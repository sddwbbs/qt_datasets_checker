-- create_db_table.sql

-- Create the database 'user_accounts'
CREATE DATABASE user_accounts;

-- Connect to the 'user_accounts' database
\c user_accounts;

-- Create the 'accounts' table
CREATE TABLE accounts (
                          id SERIAL PRIMARY KEY,
                          username VARCHAR(50) NOT NULL,
                          password VARCHAR(100) NOT NULL
);
