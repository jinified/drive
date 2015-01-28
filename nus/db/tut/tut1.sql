create table books (
title varchar(20),
format varchar(10),
page_num number,
authors varchar(20),
publisher varchar(10),
year number,
edition number,
isbn0 varchar(20),
isbn13 varchar(20))
/
drop table books
/
create table books(
title varchar2(50) not null,
format varchar2(50),
page_num number,
authors varchar2(50),
publisher varchar2(50),
year number,
edition number,
isbn0 varchar2(20) not null,
isbn13 varchar2(20) primary key,
constraint on_format check(format in('paperback','hardcover')))
/
insert into books values(
'An Introduction to Database Systems',
'paperback',
1024,
'C.J Date',
'Addison-Wesley',
2003,
8,
'0321197844',
'978-0321197849')
/
insert into books values(
'SQL and Relational Theory: How to Write Accurate SQL Code',
'paperback',
448,
'C.J Date',
'O''Reilly Media',
2011,
2,
'1449316409',
'978-1449316402')
/
select * from books
/
update books
set authors='Christopher'
where authors='C.J Date'
/
delete from books where authors='Christopher'
/
insert into books values(
'Introduction to Database Systems',
'paperback',
1024,
'C.J Date',
'Addison-Wesley',
2003,
8,
'0321197844',
'978-0321197849')
/
select title from books
/
select authors from books where title='Introduction to Database Systems'
/
alter table books add language varchar(20) default 'English'
/
drop table books
/
