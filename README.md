# NetFlick-Data-Structure-Project


```plaintext
NetFlick/
├── src/
│   ├── data_structures/      # Core DS implementations
│   │   ├── CompressedTrie.cpp
│   │   ├── CompressedTrie.h
│   │   ├── SplayTree.cpp
│   │   ├── SplayTree.h
│   │   ├── HashClass.cpp
│   │   ├── HashClass.h
│   │   ├── RadixSort.cpp
│   │   └── RadixSort.h
│   ├── features/             # User‐facing features
│   │   ├── FavoriteList.cpp
│   │   ├── FavoriteList.h
│   │   ├── UserManagement.cpp
│   │   └── UserManagement.h
│   ├── models/               # Domain models
│   │   ├── MovieSeries.cpp
│   │   └── MovieSeries.h
│   └── main.cpp              # CLI entry point
├── docs/                     # Project documentation
│   └── DS_Project_2.pdf
|
└── README.md                 # ← this file
```

---

````markdown
# NetFlick

A command‑line movie & series management and recommendation system  
built with custom data structures for fast search, sort, and access.

---


## Features

- **Prefix Search** on titles via **CompressedTrie**  
- **Self‑adjusting Access** to popular items with **SplayTree**  
- **Fast Filtering & Sorting** using **HashClass** and **RadixSort**  
- **Favorites List** management (add/remove, alphabetical sort)  
- **User/Admin Management** for entry CRUD operations  
- Intuitive **CLI** menu for all operations

---

## Folder Structure

```plaintext
NetFlick/
├── src/
│   ├── data_structures/
│   ├── features/
│   ├── models/
│   └── main.cpp
├── docs/
│   └── DS_Project_2.pdf
|
└── README.md
````

* **`src/data_structures/`**:

  * `CompressedTrie.*`
  * `SplayTree.*`
  * `HashClass.*`
  * `RadixSort.*`
* **`src/features/`**:

  * `FavoriteList.*`
  * `UserManagement.*`
* **`src/models/`**:

  * `MovieSeries.*`
* **`src/main.cpp`**: CLI entry point
* **`docs/`**: Project spec and design (PDF)


---

## Building

```bash
git clone https://github.com/Paya38/NetFlick-Data-Structure-Project.git
cd NetFlick-Data-Structure-Project

```

Follow on‑screen prompts to:

* Search by title prefix
* Filter & sort by year, genre, rating
* Manage your favorites list
* (Admin) Add/Edit/Delete movies & series

---
