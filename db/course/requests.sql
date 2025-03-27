INSERT INTO Roles (name, description)
VALUES
    ('Администратор', 'Отвечает за управление системой, управление пользователями и данными библиотеки'),
    ('Библиотекарь', 'Обрабатывает выдачу и возврат книг, управляет бронированиями'),
    ('Читатель', 'Может бронировать, брать книги в аренду и оставлять отзывы'),
    ('Модератор', 'Отвечает за контроль контента, модерирует отзывы и комментарии');
select * from roles;

INSERT INTO Authors (first_name, last_name, bio)
VALUES
    ('Лев', 'Толстой', 'Русский писатель, автор произведений «Война и мир» и «Анна Каренина».'),
    ('Фёдор', 'Достоевский', 'Русский писатель, автор «Преступление и наказание» и «Братья Карамазовы».'),
    ('Александр', 'Пушкин', 'Русский поэт, драматург и прозаик, основоположник современного русского литературного языка.'),
    ('Антон', 'Чехов', 'Русский писатель и драматург, мастер короткого рассказа.'),
    ('Иван', 'Тургенев', 'Русский писатель, автор романа «Отцы и дети».'),
    ('Михаил', 'Булгаков', 'Русский писатель, автор «Мастер и Маргарита».'),
    ('Николай', 'Гоголь', 'Русский писатель, драматург, автор «Мёртвые души».'),
    ('Максим', 'Горький', 'Русский писатель, драматург, публицист, автор пьесы «На дне».'),
    ('Владимир', 'Маяковский', 'Русский поэт, драматург, представитель футуризма.'),
    ('Андрей', 'Платонов', 'Русский писатель, автор «Котлован».');
select * from authors;

INSERT INTO LibraryBranches (name, address, phone_number)
VALUES
    ('Центральная библиотека', 'г. Минск, ул. Ленина, д. 10', '+375 (17) 123-4567'),
    ('Северный филиал', 'г. Витебск, ул. Суворова, д. 20', '+375 (212) 234-5678'),
    ('Южный филиал', 'г. Гомель, ул. Интернациональная, д. 15', '+375 (232) 345-6789'),
    ('Западный филиал', 'г. Брест, ул. Московская, д. 25', '+375 (162) 456-7890');
select * from librarybranches;

INSERT INTO ReadingRooms (branch_id, name, capacity, location)
VALUES
    ((SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'),
     'Читальный зал №1',
     50,
     '1 этаж, рядом с отделом выдачи'),
    ((SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'),
     'Читальный зал №2',
     30,
     '2 этаж, рядом с архивом'),

    ((SELECT id FROM LibraryBranches WHERE name = 'Северный филиал'),
     'Читальный зал №1',
     40,
     '1 этаж, у входа'),
    ((SELECT id FROM LibraryBranches WHERE name = 'Северный филиал'),
     'Читальный зал №2',
     25,
     '2 этаж, у окна'),

    ((SELECT id FROM LibraryBranches WHERE name = 'Южный филиал'),
     'Читальный зал №1',
     35,
     '1 этаж, напротив ресепшена'),
    ((SELECT id FROM LibraryBranches WHERE name = 'Южный филиал'),
     'Читальный зал №2',
     20,
     '2 этаж, рядом с архивом'),

    ((SELECT id FROM LibraryBranches WHERE name = 'Западный филиал'),
     'Читальный зал №1',
     45,
     '1 этаж, справа от входа'),
    ((SELECT id FROM LibraryBranches WHERE name = 'Западный филиал'),
     'Читальный зал №2',
     30,
     '2 этаж, у окна');
select * from readingrooms;

DO $$
BEGIN
    CALL add_user('alex123', 'alex123@example.com', 'hashed_password1');
    CALL add_user('maria2024', 'maria2024@example.com', 'hashed_password2');
    CALL add_user('john_doe', 'john_doe@example.com', 'hashed_password3');
    CALL add_user('julia89', 'julia89@example.com', 'hashed_password4');
    CALL add_user('ivan_the_great', 'ivan_great@example.com', 'hashed_password5');
    CALL add_user('anna_sky', 'anna_sky@example.com', 'hashed_password6');
    CALL add_user('peter_pan', 'peter_pan@example.com', 'hashed_password7');
    CALL add_user('sophia_star', 'sophia_star@example.com', 'hashed_password8');
    CALL add_user('max_power', 'max_power@example.com', 'hashed_password9');
    CALL add_user('kate_wonder', 'kate_wonder@example.com', 'hashed_password10');
END;
$$ LANGUAGE plpgsql;

select * from useractivity;

INSERT INTO Complaints (user_id, content, status, created_at)
VALUES
    (3, 'Книга "Война и мир" оказалась повреждена.', 'open', NOW()),
    (4, 'Пропуск доступа в читальный зал не работает.', 'open', NOW() - INTERVAL '1 day'),
    (5, 'Задержка с обновлением доступных книг.', 'in_progress', NOW() - INTERVAL '2 days'),
    (6, 'Неправильно учтена дата возврата книги.', 'resolved', NOW() - INTERVAL '3 days'),
    (7, 'Читальный зал был закрыт раньше указанного времени.', 'open', NOW() - INTERVAL '4 days');

select * from users ORDER BY id DESC;
select * from useractivity ORDER BY id DESC;
select * from profiles ORDER BY id DESC;

INSERT INTO Attendance (user_id, timestamp, reading_room_id)
SELECT
    (SELECT id FROM Users WHERE username = 'alex123'),
    NOW() - INTERVAL '1 day',
    (SELECT id FROM ReadingRooms WHERE name = 'Читальный зал №1' AND branch_id = (SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'))
WHERE EXISTS (SELECT id FROM Users WHERE username = 'alex123')
  AND EXISTS (SELECT id FROM ReadingRooms WHERE name = 'Читальный зал №1' AND branch_id = (SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'))
UNION ALL
SELECT
    (SELECT id FROM Users WHERE username = 'maria2024'),
    NOW() - INTERVAL '2 hours',
    (SELECT id FROM ReadingRooms WHERE name = 'Читальный зал №2' AND branch_id = (SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'))
WHERE EXISTS (SELECT id FROM Users WHERE username = 'maria2024')
  AND EXISTS (SELECT id FROM ReadingRooms WHERE name = 'Читальный зал №2' AND branch_id = (SELECT id FROM LibraryBranches WHERE name = 'Центральная библиотека'));
select * from attendance;

INSERT INTO Categories (name, description)
VALUES
    ('Художественная литература', 'Книги, которые включают романы, рассказы, поэзию и драматургию.'),
    ('Научная литература', 'Книги, связанные с исследованиями, научными теориями и открытиями.'),
    ('Учебная литература', 'Учебники, справочники и другие материалы для обучения.'),
    ('Детская литература', 'Книги для детей, включая сказки, рассказы и стихи.'),
    ('Фантастика', 'Произведения о вымышленных мирах, науке и технологиях.'),
    ('Приключения', 'Книги о путешествиях, приключениях и опасных ситуациях.'),
    ('Историческая литература', 'Книги, основанные на исторических событиях и личностях.'),
    ('Психология и саморазвитие', 'Книги, посвященные личностному росту, психологии и мотивации.'),
    ('Медицинская литература', 'Книги для врачей, студентов-медиков и интересующихся медициной.'),
    ('Искусство и культура', 'Книги о живописи, музыке, театре и других формах искусства.');
select * from categories;

INSERT INTO Publishers (name, address)
VALUES
    ('Издательство "Просвещение"', 'г. Москва, ул. Тверская, д. 8'),
    ('Издательство "Молодая гвардия"', 'г. Санкт-Петербург, пр. Невский, д. 22'),
    ('Издательство "Эксмо"', 'г. Москва, ул. Пушкина, д. 15'),
    ('Издательство "АСТ"', 'г. Екатеринбург, ул. Ленина, д. 5'),
    ('Издательство "Росмэн"', 'г. Казань, ул. Баумана, д. 12'),
    ('Издательство "МИФ"', 'г. Новосибирск, ул. Красный проспект, д. 30'),
    ('Издательство "Феникс"', 'г. Ростов-на-Дону, ул. Чехова, д. 19'),
    ('Издательство "Азбука-Аттикус"', 'г. Минск, ул. Независимости, д. 16'),
    ('Издательство "Вече"', 'г. Брест, ул. Советская, д. 10'),
    ('Издательство "Питер"', 'г. Гомель, ул. Советская, д. 7');
select * from publishers;

DO $$
BEGIN
    CALL add_book_with_branch(
        'Война и мир',
        1,
        ARRAY[1, 2],
        1,
        'русский',
        '978-5-94878-004-7',
        1869,
        1,
        5
    );

    CALL add_book_with_branch(
        'Преступление и наказание',
        2,
        ARRAY[1, 3],
        2,
        'русский',
        '978-5-699-12030-7',
        1866,
        2,
        3
    );

    CALL add_book_with_branch(
        'Анна Каренина',
        1,
        ARRAY[1],
        1,
        'русский',
        '978-5-94878-015-3',
        1877,
        1,
        7
    );

    CALL add_book_with_branch(
        'Мастер и Маргарита',
        6,
        ARRAY[1, 4],
        3,
        'русский',
        '978-5-699-01449-6',
        1967,
        3,
        4
    );

    CALL add_book_with_branch(
        'Мёртвые души',
        7,
        ARRAY[1, 5],
        4,
        'русский',
        '978-5-17-081140-2',
        1842,
        4,
        6
    );
END;
$$ LANGUAGE plpgsql;

INSERT INTO Users (username, email, password_hash, role_id, is_reviewer, created_at)
VALUES
    ('librarian_1', 'librarian1@example.com', 'hashed_password1', 2, FALSE, NOW()),
    ('librarian_2', 'librarian2@example.com', 'hashed_password2', 2, FALSE, NOW());

INSERT INTO CriticApplications (user_id, application_date, status, review_comments)
VALUES
    (3, NOW(), 'pending', NULL),
    (4, NOW() - INTERVAL '1 day', 'pending', 'Отличная работа, комментарии соответствуют требованиям.'),
    (5, NOW() - INTERVAL '2 days', 'rejected', 'Не хватает аналитики в отзыве.'),
    (6, NOW() - INTERVAL '3 days', 'pending', NULL),
    (7, NOW() - INTERVAL '4 days', 'pending', 'Комментарий содержит полезные рекомендации.');
select * from criticapplications;
select *
from users;

INSERT INTO BookReviewsVotes (review_id, user_id, vote_type)
VALUES
    (1, 2, 'up'),
    (1, 3, 'down'),
    (1, 4, 'up');
select * from bookreviewsvotes;
SELECT
    review_id,
    COUNT(CASE WHEN vote_type = 'up' THEN 1 END) AS up_votes,
    COUNT(CASE WHEN vote_type = 'down' THEN 1 END) AS down_votes
FROM BookReviewsVotes
GROUP BY review_id
ORDER BY review_id;

INSERT INTO EBooks (title, author_id, category_id, publisher_id, publication_year, language, file_path, file_format)
VALUES
    ('Программирование на Python', 1, 6, 1, 2022, 'русский', '/ebooks/python_programming.pdf', 'pdf'),
    ('Современный JavaScript', 2, 6, 2, 2021, 'русский', '/ebooks/modern_javascript.epub', 'epub'),
    ('Введение в искусственный интеллект', 3, 7, 3, 2023, 'английский', '/ebooks/intro_to_ai.mobi', 'mobi'),
    ('Обработка естественного языка', 4, 7, 1, 2020, 'английский', '/ebooks/nlp_processing.pdf', 'pdf'),
    ('Разработка игр на Unity', 5, 6, 4, 2019, 'русский', '/ebooks/game_development_unity.epub', 'epub'),
    ('Базы данных для начинающих', 6, 6, 3, 2022, 'русский', '/ebooks/databases_for_beginners.mobi', 'mobi'),
    ('Классика алгоритмов', 7, 7, 2, 2018, 'английский', '/ebooks/classic_algorithms.pdf', 'pdf'),
    ('Практическое машинное обучение', 8, 7, 4, 2021, 'английский', '/ebooks/practical_ml.epub', 'epub');
select * from ebooks;

INSERT INTO Events (branch_id, name, description, start_time, end_time)
VALUES
    (1, 'Литературный вечер', 'Встреча с местными авторами и чтение произведений.', '2024-01-15 18:00:00', '2024-01-15 20:00:00'),
    (2, 'Книжная ярмарка', 'Обмен книгами и специальные скидки на популярные издания.', '2024-02-01 10:00:00', '2024-02-01 16:00:00'),
    (3, 'Мастер-класс по писательскому мастерству', 'Советы по написанию книг от профессиональных писателей.', '2024-03-10 14:00:00', '2024-03-10 17:00:00'),
    (4, 'Детский день', 'Игры, чтение и конкурсы для детей.', '2024-04-05 12:00:00', '2024-04-05 15:00:00'),
    (1, 'Вечер настольных игр', 'Попробуйте различные настольные игры в уютной обстановке.', '2024-01-22 17:00:00', '2024-01-22 19:00:00'),
    (2, 'Фотовыставка', 'Фотографии на тему "Город и книги".', '2024-02-15 11:00:00', '2024-02-15 15:00:00'),
    (3, 'Кинопоказ', 'Показ экранизации классического романа.', '2024-03-20 18:00:00', '2024-03-20 21:00:00'),
    (4, 'Читательский клуб', 'Обсуждение произведения месяца.', '2024-04-10 16:00:00', '2024-04-10 18:00:00');
select * from events;

INSERT INTO Favorites (user_id, book_id, added_at)
VALUES
    (3, 1, NOW()),
    (4, 2, NOW() - INTERVAL '1 day'),
    (5, 3, NOW() - INTERVAL '2 days'),
    (6, 4, NOW() - INTERVAL '3 days'),
    (7, 5, NOW() - INTERVAL '4 days'),
    (3, 2, NOW() - INTERVAL '5 days'),
    (4, 3, NOW() - INTERVAL '6 days'),
    (5, 4, NOW() - INTERVAL '7 days'),
    (6, 5, NOW() - INTERVAL '8 days'),
    (7, 1, NOW() - INTERVAL '9 days');
select  * from favorites;

INSERT INTO Feedbacks (user_id, book_id, content, created_at)
VALUES
    (3, 1, 'Очень интересная книга, рекомендую к прочтению!', NOW()),
    (4, 2, 'Хорошая книга, но местами слишком много подробностей.', NOW() - INTERVAL '1 day'),
    (5, 3, 'Отличный стиль автора, книга захватывает с первых страниц.', NOW() - INTERVAL '2 days'),
    (6, 4, 'Сюжет увлекательный, но немного затянут.', NOW() - INTERVAL '3 days'),
    (7, 5, 'Не совсем то, что я ожидал, но все равно достойно.', NOW() - INTERVAL '4 days');
select * from feedbacks;

INSERT INTO FeedbackRatings (feedback_id, user_id, rating)
VALUES
    (2, 5, 3),
    (2, 6, 4),
    (3, 7, 5),
    (3, 3, 4),
    (4, 2, 3),
    (4, 4, 4),
    (5, 6, 5),
    (5, 7, 3);
select * from feedbacks;



INSERT INTO Fines (user_id, amount, description, created_at)
VALUES
    (1, 50.00, 'Штраф за просрочку возврата книги', NOW()),
    (2, 100.00, 'Штраф за утерю книги', NOW()),
    (3, 25.00, 'Штраф за повреждение книги', NOW()),
    (4, 75.00, 'Штраф за неявку на мероприятие', NOW()),
    (1, 150.00, 'Повторный штраф за утерю книги', NOW());


INSERT INTO LostBooks (book_id, user_id, reported_date, status)
VALUES
    (1, 1, '2024-12-01', 'pending'),
    (2, 2, '2024-12-05', 'resolved'),
    (3, 3, '2024-12-10', 'pending'),
    (4, 4, '2024-12-15', 'resolved'),
    (1, 5, '2024-12-20', 'pending');


INSERT INTO Notifications (user_id, content, created_at, read_status)
VALUES
    (1, 'Ваша книга "Основы программирования" просрочена. Пожалуйста, верните её в библиотеку.', '2024-12-20 10:00:00', FALSE),
    (2, 'Ваш запрос на бронирование книги "Алгоритмы и структуры данных" одобрен.', '2024-12-18 15:30:00', TRUE),
    (3, 'Книга "Математический анализ" доступна для выдачи.', '2024-12-19 09:45:00', FALSE),
    (4, 'Вы записаны на мероприятие "Читательский клуб" 25 декабря 2024 года.', '2024-12-15 08:20:00', TRUE),
    (5, 'Штраф за утерю книги "Теория вероятностей" добавлен на ваш счёт.', '2024-12-22 14:00:00', FALSE);

INSERT INTO Reservations (book_id, user_id, reservation_date, status)
VALUES
    (1, 1, '2024-12-20 10:00:00', 'active'),
    (2, 2, '2024-12-18 15:30:00', 'completed'),
    (3, 3, '2024-12-19 09:45:00', 'active'),
    (4, 4, '2024-12-15 08:20:00', 'cancelled'),
    (5, 5, '2024-12-22 14:00:00', 'active');

INSERT INTO Tags (name, book_id)
VALUES
    ('Программирование', 1),
    ('Алгоритмы', 2),
    ('Математика', 3),
    ('Наука', 4),
    ('Классика', 5),
    ('Технологии', 1),
    ('История', 5);

INSERT INTO WishList (user_id, book_id, added_at)
VALUES
    (1, 1, '2024-12-20 10:00:00'),
    (2, 3, '2024-12-18 15:30:00'),
    (3, 2, '2024-12-19 09:45:00'),
    (4, 5, '2024-12-15 08:20:00'),
    (5, 4, '2024-12-22 14:00:00');



