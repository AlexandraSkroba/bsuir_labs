-- Вставка тестовых данных в таблицу roles
INSERT INTO roles (role_name)
VALUES ('Admin'), ('Writer'), ('Reader');

-- Вставка тестовых данных в таблицу users
INSERT INTO users (username, email, password, role_id) VALUES
('admin', 'admin@gmail.com', 'admin123', 1),
('StellarNomad', 's.tellar@gmail.com', 'nskajk72', 3),
('QuantumDreamer', 'dddreamer@gmail.com', 'kTFbkj80', 3),
('ProseForge', 'proseffforge@gmail.com', 'prpFF123', 2);

INSERT INTO users (username, email, password, role_id) VALUES
('QuillQuest', 'qqqqU.est@gmail.com', 'jdlbo628II', 2);

INSERT INTO profile (user_id, name, biography, date_of_birth, gender) VALUES
(1, 'Alexandra Skroba', '', '2004-01-01', 'F'),
(2, 'Jane Doe', 'A short biography about Jane Doe.', '1992-02-02', 'F'),
(3, 'Alex Smith', 'Biography for Alex Smith.', '1985-05-15', 'M'),
(4, 'Emily Johnson', 'A short biography about Emily Johnson.', '1988-08-08', 'F'),
(5, 'Michael Brown', 'Biography for Michael Brown.', '1995-11-21', 'M');

-- Добавление статей в таблицу articles
INSERT INTO articles (author_id, title, content, published_at) VALUES
(4, 'Introduction to SQL', 'This is an introduction to SQL content.', '2023-01-01 10:00:00'),
(4, 'Web Development Best Practices', 'Best practices for web development.', '2023-02-15 14:30:00'),
(4, 'Data Science in Python', 'Overview of data science using Python.', '2023-03-10 08:45:00'),
(5, 'UX Design Principles', 'Principles for effective UX design.', '2023-04-05 12:15:00'),
(5, 'Machine Learning Basics', 'Basic concepts of machine learning.', '2023-05-20 17:00:00');

INSERT INTO articles (author_id, title, content, published_at) VALUES
(4, 'Sustainable Horizons: Eco-Friendly Innovations Reshaping Industries',
    'Sustainable horizons content.', '2023-05-11 10:00:00'),
(4, 'Green Tomorrow: Evolution of Eco-Conscious Technologies',
    'Green tomorrow content.', '2023-06-14 10:00:00'),
(4, 'EcoRevolution: Advancing Sustainability Across Disciplines',
    'EcoRevolution content.', '2023-11-01 10:00:00'),
(4, 'Nature-Inspired Progress: Charting the Course for EcoEvolve',
    'Nature-inspired progress content.', '2023-11-27 10:00:00'),
(4, 'From Green Ideas to Green Actions: Driving the EcoEvolve Movement',
    'Green ideas content.', '2023-12-04 10:00:00');


-- Добавление изображений в таблицу images
INSERT INTO images (image_url, article_id, profile_id) VALUES
('https://example.com/image1.jpg', 1, NULL),
('https://example.com/image2.jpg', 2, NULL),
('https://example.com/image3.jpg', NULL, 1),
('https://example.com/image4.jpg', NULL, 2),
('https://example.com/image5.jpg', 3, NULL);

-- Добавление уведомлений в таблицу notifications
INSERT INTO notifications (user_id, notification_text) VALUES
(2, 'You have a new message.'),
(4, 'Your article has been published.'),
(4, 'New follower: Michael Brown.'),
(5, 'Important announcement: System update scheduled.');

-- Добавление комментариев в таблицу comments
INSERT INTO comments (user_id, article_id, comment_text, comment_date) VALUES
(1, 1, 'Great article!', '2023-01-02 12:30:00'),
(2, 1, 'I learned a lot, thank you!', '2023-01-03 08:45:00'),
(3, 2, 'Interesting insights.', '2023-02-16 15:20:00'),
(4, 3, 'Well written!', '2023-03-11 10:00:00'),
(5, 3, 'Looking forward to more content.', '2023-03-12 18:30:00');

-- Добавление категорий
INSERT INTO categories (category_name) VALUES
('Programming'),
('Web Development'),
('Data Science'),
('Design'),
('Machine Learning');

-- Связь многие ко многим между статьями и категориями
INSERT INTO article_category (article_id, category_id) VALUES
(1, 1), -- Introduction to SQL -> Programming
(1, 3), -- Introduction to SQL -> Data Science
(2, 2), -- Web Development Best Practices -> Web Development
(3, 3), -- Data Science in Python -> Data Science
(4, 4), -- UX Design Principles -> Design
(5, 5), -- Machine Learning Basics -> Machine Learning
(5, 1); -- Machine Learning Basics -> Programming

-- Добавление тегов
INSERT INTO tags (tag_name) VALUES
('SQL'),
('Python');

INSERT INTO tags (tag_name) VALUES
('EcoEvolve');

-- Связь многие ко многим между статьями и тегами
INSERT INTO articles_tags (article_id, tag_id) VALUES
(1, 1), -- Introduction to SQL -> SQL
(3, 2), -- Data Science in Python -> Python
(5, 1); -- Machine Learning Basics -> SQL

INSERT INTO articles_tags (article_id, tag_id) VALUES
(1, 3),
(3, 3);


INSERT INTO favorites (user_id, article_id) VALUES
(2, 2), -- Guest -> Web Development Best Practices
(3, 3), -- StellarNomad -> Data Science in Python
(4, 4), -- QuantumDreamer -> UX Design Principles
(5, 5), -- Emily Johnson -> Machine Learning Basics
(3, 1); -- StellarNomad -> Introduction to SQL (еще одна статья)

-- Добавление записей в таблицу ratings
INSERT INTO ratings (user_id, article_id, comment_id) VALUES
(2, 1, NULL), -- Guest лайкнул Introduction to SQL
(3, 2, NULL), -- StellarNomad лайкнул Web Development Best Practices
(4, 3, NULL), -- QuantumDreamer лайкнул Data Science in Python
(5, 4, NULL), -- Emily Johnson лайкнул UX Design Principles
(2, NULL, 1),
(3, NULL, 4),
(2, NULL, 5);

-- Добавление записей в таблицу user_activity
INSERT INTO user_activity (user_id, activity_type, date) VALUES
(1, 'Login', '2023-01-02 08:30:00'),
(1, 'Comment', '2023-01-02 09:45:00'),
(3, 'Login', '2023-02-16 14:00:00'),
(3, 'Post Article', '2023-02-16 14:20:00'),
(4, 'Login', '2023-03-11 09:40:00'),
(4, 'Comment', '2023-03-11 09:45:00'),
(4, 'Like', '2023-03-11 09:47:00'),
(5, 'Login', '2023-04-05 9:00:00'),
(5, 'Logout', '2023-04-05 11:30:00');
