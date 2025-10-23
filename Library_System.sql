create database Library_System
use Library_System
create table book (id int primary key, name varchar(10),quantity int, borrowed int,ID_librarian int references librarian(id))
create table [user] (id int primary key,Fname varchar(10),Lname varchar(10),id_librarian int references librarian (id))
create table user_book(id_user int references [user](id),id_book int references book(id)
primary key(id_user,id_book)
)
create table librarian(id int primary key,Fname varchar(10),Lname varchar(10),hiringData int,city varchar(10),street varchar(10),bDate int)
create table librarian_phone(id_librarian int references librarian(id),phone int
primary key(id_librarian,phone)
)