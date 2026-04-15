[Back to Portfolio](/index.md)

Creation of a Website that includes information about me and several labs from the Applied Networking course.
===============

-   **Class: CSCI 332** 
-   **Grade: A** 
-   **Language(s): HTML, C++, PHP, CSS** 
-   **Source Code Repository:** [Applied Networking Website](https://github.com/wbcarpenter/CSCI332Website.git)  
    (Please [email me](mailto:wbcarpenter@student.csuniv.edu?subject=GitHub%20Access) to request access.)

## Project description



## How to run the program

How to compile (if applicable) and run the project.

```bash
cd ./client
npm install
npm test
```

If you wish to run the full DreamBuy application:
```bash
# Terminal 1 – Backend
cd ./server
npm install
npm start

# Terminal 2 – Frontend
cd ./client
npm install
npm start
```

## UI Design

Although this project focused on testing rather than UI creation, the DreamBuy interface includes several user-facing components that were central to the test suit:

### Product Catalog Page

Users can browse, search, filter, and add products to their cart.
Tests validated:
- search filtering
- add-to-cart behavior
- guest-user restrictions

![DreamBuyUI](images/DreamBuyUI.png)  
Fig 1. Product Catalog interface

### Cart Page

Displays selected items, quantities, and pricing.
Tests validated:
- quantity updates
- item removal
- API interactions

![Cart](images/Cart.jpeg)  
Fig 2. Cart interface with item controls

### Checkout Page

Allows users to select shipping address and payment method.
Tests validated:
- form validation
- error messages
- order submission

![Checkout](images/Checkout.jpeg)  
Fig 3. Checkout form with validation feedback

## 3. Additional Considerations

As part of this project, I created a Maintenance Plan outlining how DreamBuy should be tested and maintained as new features are added. The plan identifies critical components (Cart, Login, Checkout, ProductCatalog) and specifies future tests such as:
- Search and filter tests
- Login error‑handling tests
- Cart interaction tests
- Order submission tests

The plan also recommends:
- Running npm test regularly
- Using Git pre‑commit hooks
- Updating mocks and dependencies
- Adding new tests alongside new features

This ensures DreamBuy remains stable and maintainable as the codebase grows.

[Back to Portfolio](/index.md)