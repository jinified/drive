CREATE TABLE book (
title VARCHAR(256) NOT NULL,
format CHAR(9) CHECK(format = 'paperback' OR format='hardcover'),
pages INT,
language VARCHAR(32),
authors VARCHAR(256),
publisher VARCHAR(64),
year DATE,
ISBN10 CHAR(10) NOT NULL UNIQUE,
ISBN13 CHAR(14) PRIMARY KEY
);

CREATE TABLE student (
name VARCHAR(32) NOT NULL,
email VARCHAR(256) PRIMARY KEY,
year DATE NOT NULL,
faculty VARCHAR(62) NOT NULL,
department VARCHAR(32) NOT NULL,
graduate DATE,
CHECK(graduate >= year)
);

CREATE TABLE copy (
owner VARCHAR(256) REFERENCES student(email) ON DELETE CASCADE,
book CHAR(14) REFERENCES book(ISBN13),
copy INT CHECK(copy>0),
available VARCHAR(6) CHECK(available = 'TRUE' OR available='FALSE'),
PRIMARY KEY (owner, book, copy)
);

CREATE TABLE loan (
borrower VARCHAR(256) REFERENCES student(email),
owner VARCHAR(256),
book CHAR(14),
copy INT,
borrowed DATE,
returned DATE,
FOREIGN KEY (owner, book, copy) REFERENCES copy(owner, book, copy) ON DELETE CASCADE,
PRIMARY KEY (borrowed, borrower, owner, book, copy),
CHECK(returned >= borrowed)
);

