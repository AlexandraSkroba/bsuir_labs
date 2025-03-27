--Create tables

CREATE TABLE IF NOT EXISTS roles (
    id SERIAL PRIMARY KEY NOT NULL,
    role_name VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY NOT NULL,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL
        CHECK (email ~* '^[A-Za-z0-9._%+-]+@[A-Za-z0-9-]+\.[A-Za-z]{2,}$'),
    password VARCHAR(50) NOT NULL,
    role_id INT NOT NULL,
    CONSTRAINT fk_role
      FOREIGN KEY(role_id)
	  REFERENCES roles(id)
);

--CREATE TYPE gender AS ENUM ('Male', 'Female', 'Unknown');
--DROP TYPE gender;

CREATE DOMAIN gender CHAR(1)
    CHECK (value IN ( 'F' , 'M' ) );

CREATE TABLE IF NOT EXISTS profile (
    id SERIAL PRIMARY KEY NOT NULL,
    user_id INT UNIQUE NOT NULL,
    name VARCHAR(50),
    biography TEXT,
    date_of_birth DATE,
    gender VARCHAR(10),
    CONSTRAINT fk_user
        FOREIGN KEY(user_id)
        REFERENCES users(id)
);

DROP TABLE IF EXISTS user_activity;

CREATE TABLE IF NOT EXISTS user_activity (
    id SERIAL PRIMARY KEY NOT NULL,
    user_id INT NOT NULL ,
    activity_type VARCHAR(255) NOT NULL,
    date TIMESTAMP NOT NULL,
    CONSTRAINT fk_user
        FOREIGN KEY(user_id)
        REFERENCES users(id)
        ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS articles (
    id SERIAL PRIMARY KEY NOT NULL,
    author_id INT NOT NULL,
    title VARCHAR(200) NOT NULL,
    content TEXT NOT NULL,
    published_at TIMESTAMP NOT NULL,
    --published_at DATE DEFAULT now()
    CONSTRAINT fk_user
        FOREIGN KEY(author_id)
        REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS images (
    id SERIAL PRIMARY KEY NOT NULL,
    image_url TEXT NOT NULL ,
    article_id INT,
    profile_id INT UNIQUE,
    CONSTRAINT fk_articles
        FOREIGN KEY(article_id)
        REFERENCES articles(id),
    CONSTRAINT fk_profile
        FOREIGN KEY(profile_id)
        REFERENCES profile(id)
);

CREATE TABLE IF NOT EXISTS notifications (
    id SERIAL PRIMARY KEY NOT NULL,
    user_id INT,
    notification_text TEXT NOT NULL,
    CONSTRAINT fk_user
        FOREIGN KEY(user_id)
        REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS comments (
    id SERIAL PRIMARY KEY NOT NULL,
    user_id INT NOT NULL,
    article_id INT NOT NULL,
    comment_text VARCHAR(200) NOT NULL,
    comment_date TIMESTAMP NOT NULL,
    CONSTRAINT fk_user
        FOREIGN KEY(user_id)
        REFERENCES users(id),
    CONSTRAINT fk_articles
        FOREIGN KEY(article_id)
        REFERENCES articles(id)
);

CREATE TABLE IF NOT EXISTS ratings (
    id SERIAL PRIMARY KEY NOT NULL,
    user_id INT NOT NULL,
    article_id INT,
    comment_id INT,
    CONSTRAINT fk_user
        FOREIGN KEY(user_id)
        REFERENCES users(id),
    CONSTRAINT fk_articles
        FOREIGN KEY(article_id)
        REFERENCES articles(id),
    CONSTRAINT fk_comments
        FOREIGN KEY(comment_id)
        REFERENCES comments(id)
);

CREATE TABLE IF NOT EXISTS article_category (
    article_id INT NOT NULL,
    category_id INT NOT NULL,
    PRIMARY KEY (article_id, category_id),
    FOREIGN KEY (article_id) REFERENCES articles(id),
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

CREATE TABLE IF NOT EXISTS categories (
    id SERIAL PRIMARY KEY NOT NULL,
    category_name VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS articles_tags (
    article_id INT NOT NULL ,
    tag_id INT NOT NULL,
    PRIMARY KEY (article_id, tag_id),
    FOREIGN KEY (article_id) REFERENCES articles(id),
    FOREIGN KEY (tag_id) REFERENCES tags(id)
);

CREATE TABLE IF NOT EXISTS tags (
    id SERIAL PRIMARY KEY NOT NULL,
    tag_name VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS favorites (
    user_id INT NOT NULL,
    article_id INT NOT NULL,
    PRIMARY KEY(user_id, article_id),
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (article_id) REFERENCES articles(id)
);
