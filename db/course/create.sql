-- Создание таблицы Roles
CREATE TABLE Roles (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) UNIQUE NOT NULL,
    description TEXT
);

-- Создание таблицы Users
CREATE TABLE Users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(256) NOT NULL,
    role_id INT NOT NULL REFERENCES Roles(id),
    is_reviewer BOOLEAN NOT NULL,
    created_at TIMESTAMP NOT NULL
);

-- Создание таблицы Profiles
CREATE TABLE Profiles (
    id SERIAL PRIMARY KEY,
    user_id INT UNIQUE NOT NULL REFERENCES Users(id),
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    phone_number VARCHAR(15) NOT NULL,
    address TEXT
);

-- Создание таблицы Authors
CREATE TABLE Authors (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    bio TEXT
);

-- Создание таблицы Categories
CREATE TABLE Categories (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) UNIQUE NOT NULL,
    description TEXT
);

-- Создание таблицы Publishers
CREATE TABLE Publishers (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) UNIQUE NOT NULL,
    address TEXT
);

-- Создание таблицы Books
CREATE TABLE Books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    author_id INT NOT NULL REFERENCES Authors(id),
    publisher_id INT NOT NULL REFERENCES Publishers(id),
    language VARCHAR(50) NOT NULL,
    isbn VARCHAR(20) UNIQUE NOT NULL,
    published_year INT NOT NULL
);

-- Создание таблицы BookCategories
CREATE TABLE BookCategories (
    id SERIAL PRIMARY KEY,
    book_id INT NOT NULL REFERENCES Books(id),
    category_id INT NOT NULL REFERENCES Categories(id)
);

-- Создание таблицы UserActivity
CREATE TABLE UserActivity (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    activity_type VARCHAR(100) NOT NULL,
    timestamp TIMESTAMP NOT NULL
);

-- Создание таблицы Feedbacks
CREATE TABLE Feedbacks (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    book_id INT NOT NULL REFERENCES Books(id),
    content TEXT NOT NULL,
    rating NUMERIC(3, 2) DEFAULT NULL CHECK (rating >= 1 AND rating <= 5),
    created_at TIMESTAMP NOT NULL
);

-- Создание таблицы LibraryBranches
CREATE TABLE LibraryBranches (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    address TEXT NOT NULL,
    phone_number VARCHAR(20)
);

-- Создание таблицы ReadingRooms
CREATE TABLE ReadingRooms (
    id SERIAL PRIMARY KEY,
    branch_id INT NOT NULL REFERENCES LibraryBranches(id),
    name VARCHAR(100) NOT NULL,
    capacity INT NOT NULL,
    location TEXT NOT NULL
);

-- Создание таблицы Attendance
CREATE TABLE Attendance (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    timestamp TIMESTAMP NOT NULL,
    reading_room_id INT REFERENCES ReadingRooms(id)
);

-- Создание таблицы Events
CREATE TABLE Events (
    id SERIAL PRIMARY KEY,
    branch_id INT NOT NULL REFERENCES LibraryBranches(id),
    name VARCHAR(100) NOT NULL,
    description TEXT,
    start_time TIMESTAMP NOT NULL,
    end_time TIMESTAMP NOT NULL
);

-- Создание таблицы Notifications
CREATE TABLE Notifications (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    content TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL,
    read_status BOOLEAN DEFAULT FALSE
);

-- Создание таблицы Favorites
CREATE TABLE Favorites (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    book_id INT NOT NULL REFERENCES Books(id),
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- Создание таблицы BookDistribution
CREATE TABLE BookDistribution (
    id SERIAL PRIMARY KEY,
    book_id INT NOT NULL REFERENCES Books(id),
    user_id INT NOT NULL REFERENCES Users(id),
    issuer_id INT NOT NULL REFERENCES Users(id),
    issue_date TIMESTAMP NOT NULL,
    return_date TIMESTAMP NOT NULL
);

-- Создание таблицы Fines
CREATE TABLE Fines (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    amount DECIMAL(10, 2) NOT NULL,
    description TEXT,
    created_at TIMESTAMP NOT NULL
);

-- Создание таблицы Reservations
CREATE TABLE Reservations (
    id SERIAL PRIMARY KEY,
    book_id INT NOT NULL REFERENCES Books(id),
    user_id INT NOT NULL REFERENCES Users(id),
    reservation_date TIMESTAMP NOT NULL,
    status VARCHAR(20) DEFAULT 'active'
);

-- Создание таблицы Reviews
CREATE TABLE Reviews (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    book_id INT NOT NULL REFERENCES Books(id),
    content TEXT NOT NULL,
    rating INT CHECK (rating BETWEEN 1 AND 5) NOT NULL,
    created_at TIMESTAMP NOT NULL
);

-- Создание таблицы WishList
CREATE TABLE WishList (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    book_id INT NOT NULL REFERENCES Books(id),
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- Создание таблицы BookReviewsVotes
CREATE TABLE BookReviewsVotes (
    id SERIAL PRIMARY KEY,
    review_id INT NOT NULL REFERENCES Reviews(id),
    user_id INT NOT NULL REFERENCES Users(id),
    vote_type VARCHAR(10) CHECK (vote_type IN ('up', 'down')) NOT NULL
);

-- Создание таблицы Complaints
CREATE TABLE Complaints (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    content TEXT NOT NULL,
    status VARCHAR(20) DEFAULT 'open' NOT NULL,
    created_at TIMESTAMP NOT NULL
);

-- Создание таблицы LostBooks
CREATE TABLE LostBooks (
    id SERIAL PRIMARY KEY,
    book_id INT NOT NULL REFERENCES Books(id),
    user_id INT NOT NULL REFERENCES Users(id),
    reported_date TIMESTAMP NOT NULL,
    status VARCHAR(20) DEFAULT 'pending'
);

-- Создание таблицы EBooks
CREATE TABLE EBooks (
    id SERIAL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    author_id INT NOT NULL REFERENCES Authors(id),
    category_id INT NOT NULL REFERENCES Categories(id),
    publisher_id INT REFERENCES Publishers(id),
    publication_year INT NOT NULL,
    language VARCHAR(50) NOT NULL,
    file_path TEXT NOT NULL,
    file_format VARCHAR(10) NOT NULL,
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- Создание таблицы Tags
CREATE TABLE Tags (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) UNIQUE NOT NULL,
    book_id INT NOT NULL REFERENCES Books(id)
);

-- Создание таблицы CriticApplications
CREATE TABLE CriticApplications (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES Users(id),
    application_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    status VARCHAR(20) DEFAULT 'pending' NOT NULL,
    review_comments TEXT
);

-- Создание таблицы BookBranch
CREATE TABLE BookBranch (
    id SERIAL PRIMARY KEY,
    book_id INT NOT NULL REFERENCES Books(id),
    branch_id INT NOT NULL REFERENCES LibraryBranches(id),
    copies_total INT NOT NULL,
    copies_available INT NOT NULL
);

-- Создание таблицы FeedbackRatings
CREATE TABLE FeedbackRatings (
    id SERIAL PRIMARY KEY,
    feedback_id INT NOT NULL REFERENCES Feedbacks(id),
    user_id INT NOT NULL REFERENCES Users(id),
    rating INT CHECK (rating BETWEEN 1 AND 5) NOT NULL
);

ALTER TABLE Feedbacks
ALTER COLUMN rating TYPE NUMERIC(3, 2) USING rating::NUMERIC(3, 2);



-- при изменении идентификаторов связанные записи автоматически обновляются
ALTER TABLE Books
ADD CONSTRAINT fk_books_publishers
FOREIGN KEY (publisher_id)
REFERENCES Publishers(id)
ON UPDATE CASCADE;

-- при удалении записи из таблицы Books, все записи из BookBranch, связанные с удаляемой книгой, будут удаляться автоматически
ALTER TABLE BookBranch
DROP CONSTRAINT bookbranch_book_id_fkey;

ALTER TABLE BookBranch
ADD CONSTRAINT bookbranch_book_id_fkey
FOREIGN KEY (book_id) REFERENCES Books(id)
ON DELETE CASCADE;

-- для обновления или изменения правил ограничения
ALTER TABLE BookCategories
DROP CONSTRAINT bookcategories_book_id_fkey;

-- если книга удаляется из таблицы Books, то связанные записи в таблице BookCategories будут автоматически удалены
ALTER TABLE BookCategories
ADD CONSTRAINT bookcategories_book_id_fkey
FOREIGN KEY (book_id) REFERENCES Books(id)
ON DELETE CASCADE;

ALTER TABLE Profiles
DROP CONSTRAINT profiles_user_id_fkey;

ALTER TABLE Profiles
ADD CONSTRAINT profiles_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE UserActivity
DROP CONSTRAINT useractivity_user_id_fkey;

ALTER TABLE UserActivity
ADD CONSTRAINT useractivity_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE Attendance
DROP CONSTRAINT attendance_user_id_fkey;

ALTER TABLE Attendance
ADD CONSTRAINT attendance_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE Notifications
DROP CONSTRAINT notifications_user_id_fkey;

ALTER TABLE Notifications
ADD CONSTRAINT notifications_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE Fines
DROP CONSTRAINT fines_user_id_fkey;

ALTER TABLE Fines
ADD CONSTRAINT fines_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE Reservations
DROP CONSTRAINT reservations_user_id_fkey;

ALTER TABLE Reservations
ADD CONSTRAINT reservations_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE WishList
DROP CONSTRAINT wishlist_user_id_fkey;

ALTER TABLE WishList
ADD CONSTRAINT wishlist_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;

ALTER TABLE LostBooks
DROP CONSTRAINT lostbooks_user_id_fkey;

ALTER TABLE LostBooks
ADD CONSTRAINT lostbooks_user_id_fkey
FOREIGN KEY (user_id) REFERENCES Users(id)
ON DELETE CASCADE;






