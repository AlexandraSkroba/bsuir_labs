-- триггер для автоматического обновления доступных копий книг
CREATE OR REPLACE FUNCTION update_copies_available()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        UPDATE BookBranch
        SET copies_available = copies_available - 1
        WHERE book_id = NEW.book_id;
    ELSIF TG_OP = 'DELETE' THEN
        UPDATE BookBranch
        SET copies_available = copies_available + 1
        WHERE book_id = OLD.book_id;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_copies
AFTER INSERT OR DELETE ON BookDistribution
FOR EACH ROW
EXECUTE FUNCTION update_copies_available();

-- триггер для автоматического выставления штрафов за просроченные книги
CREATE OR REPLACE FUNCTION add_fine_for_overdue_books()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.return_date > NEW.issue_date + INTERVAL '30 days' THEN
        INSERT INTO Fines (user_id, amount, description, created_at)
        VALUES (NEW.user_id, 5.00, 'Overdue book fine', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_add_fine
AFTER UPDATE OF return_date ON BookDistribution
FOR EACH ROW
EXECUTE FUNCTION add_fine_for_overdue_books();

-- триггер для автоматического уведомления пользователя при создании бронирования
CREATE OR REPLACE FUNCTION notify_reservation()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO Notifications (user_id, content, created_at, read_status)
    VALUES (NEW.user_id, 'Your reservation for the book has been successfully created.', NOW(), FALSE);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_notify_reservation
AFTER INSERT ON Reservations
FOR EACH ROW
EXECUTE FUNCTION notify_reservation();

-- триггер для автоматического добавления записи в UserActivity
CREATE OR REPLACE FUNCTION log_user_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP != 'DELETE' THEN
        INSERT INTO UserActivity (user_id, activity_type, timestamp)
        VALUES (
            NEW.id,
            CASE
                WHEN TG_OP = 'INSERT' THEN 'create user'
                WHEN TG_OP = 'UPDATE' THEN 'update user'
            END,
            NOW()
        );
    END IF;
    RETURN CASE
        WHEN TG_OP = 'DELETE' THEN OLD
        ELSE NEW
    END;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_log_reservations
AFTER INSERT ON Reservations
FOR EACH ROW
EXECUTE FUNCTION log_user_activity();

CREATE TRIGGER trigger_log_reviews
AFTER INSERT ON Reviews
FOR EACH ROW
EXECUTE FUNCTION log_user_activity();

CREATE TRIGGER trigger_log_users
AFTER INSERT OR UPDATE OR DELETE ON Users
FOR EACH ROW
EXECUTE FUNCTION log_user_activity();

-- триггер для создания профиля
CREATE OR REPLACE FUNCTION create_profile_for_user()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO Profiles (user_id, first_name, last_name, phone_number, address)
    VALUES (
        NEW.id,
        NEW.username,
        '',
        '',
        NULL
    );
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_create_profile
AFTER INSERT ON Users
FOR EACH ROW
EXECUTE FUNCTION create_profile_for_user();

-- триггер для автоматического удаления просроченных бронирований
CREATE OR REPLACE FUNCTION delete_expired_reservations()
RETURNS TRIGGER AS $$
BEGIN
    DELETE FROM Reservations
    WHERE id = OLD.id AND reservation_date < NOW() - INTERVAL '7 days';

    INSERT INTO Notifications (user_id, content, created_at, read_status)
    VALUES (OLD.user_id, 'Your reservation has expired and has been removed.', NOW(), FALSE);

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_delete_expired_reservations
AFTER UPDATE OF reservation_date ON Reservations
FOR EACH ROW
WHEN (NEW.status = 'active')
EXECUTE FUNCTION delete_expired_reservations();

-- для автоматического обновления поля is_reviewer у пользователя, когда статус заявки становится approved
CREATE OR REPLACE FUNCTION update_reviewer_status()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.status = 'approved' THEN
        UPDATE Users
        SET is_reviewer = TRUE
        WHERE id = NEW.user_id;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_reviewer_status
AFTER UPDATE ON CriticApplications
FOR EACH ROW
EXECUTE FUNCTION update_reviewer_status();

-- для пересчёта среднего рейтинга
CREATE OR REPLACE FUNCTION update_feedback_rating()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE Feedbacks
    SET rating = COALESCE(
        (SELECT ROUND(AVG(rating)::NUMERIC, 2)
         FROM FeedbackRatings
         WHERE feedback_id = NEW.feedback_id),
        0 -- Установить 0, если нет оценок
    )
    WHERE id = NEW.feedback_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_feedback_rating
AFTER INSERT OR UPDATE OR DELETE ON FeedbackRatings
FOR EACH ROW
EXECUTE FUNCTION update_feedback_rating();

-- процедура для бронирования книги
CREATE OR REPLACE PROCEDURE reserve_book(p_user_id INT, p_book_id INT)
LANGUAGE plpgsql
AS $$
BEGIN
    IF (SELECT copies_available FROM Books WHERE id = p_book_id) > 0 THEN
        INSERT INTO Reservations (user_id, book_id, reservation_date, status)
        VALUES (p_user_id, p_book_id, NOW(), 'active');
        UPDATE Books
        SET copies_available = copies_available - 1
        WHERE id = p_book_id;
    ELSE
        RAISE EXCEPTION 'No copies available for reservation';
    END IF;
END;
$$;

-- процедура для добавления нового пользователя
CREATE OR REPLACE PROCEDURE add_user(p_username VARCHAR, p_email VARCHAR, p_password_hash VARCHAR)
LANGUAGE plpgsql
AS $$
BEGIN
    IF EXISTS (SELECT 1 FROM Users WHERE email = p_email) THEN
        RAISE EXCEPTION 'Email already exists';
    ELSE
        INSERT INTO Users (username, email, password_hash, role_id, is_reviewer, created_at)
        VALUES (p_username, p_email, p_password_hash, 1, FALSE, NOW());
    END IF;
END;
$$;

-- для добавления записи в таблицу Books и автоматического создания связанной записи в таблице BookBranch
CREATE OR REPLACE PROCEDURE add_book_with_branch(
    p_title VARCHAR,
    p_author_id INT,
    p_category_ids INT[],
    p_publisher_id INT,
    p_language VARCHAR,
    p_isbn VARCHAR,
    p_published_year INT,
    p_branch_id INT,
    p_copies_total INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    new_book_id INT;
    category_id INT;
BEGIN
    -- Добавление книги в таблицу Books
    INSERT INTO Books (title, author_id, publisher_id, language, isbn, published_year)
    VALUES (p_title, p_author_id, p_publisher_id, p_language, p_isbn, p_published_year)
    RETURNING id INTO new_book_id;

    -- Добавление записей в таблицу BookCategories для каждой категории
    FOREACH category_id IN ARRAY p_category_ids LOOP
        INSERT INTO BookCategories (book_id, category_id)
        VALUES (new_book_id, category_id);
    END LOOP;

    -- Добавление записи в таблицу BookBranch с количеством копий
    INSERT INTO BookBranch (book_id, branch_id, copies_total, copies_available)
    VALUES (new_book_id, p_branch_id, p_copies_total, p_copies_total);

    RAISE NOTICE 'Book added with ID %, categories linked, and branch record created with % copies.', new_book_id, p_copies_total;
END;
$$;

-- для добавления записей в BookDistribution
CREATE OR REPLACE PROCEDURE add_book_distribution(
    p_book_id INT,
    p_user_id INT,
    p_issuer_id INT,
    p_issue_date TIMESTAMP WITH TIME ZONE,
    p_return_date TIMESTAMP WITH TIME ZONE
)
LANGUAGE plpgsql
AS $$
DECLARE
    issuer_role_id INT;
    book_exists BOOLEAN;
BEGIN
    -- Проверка роли пользователя, выдающего книгу
    SELECT role_id INTO issuer_role_id
    FROM Users
    WHERE id = p_issuer_id;

    IF issuer_role_id != 2 THEN
        RAISE EXCEPTION 'User with ID % is not a librarian.', p_issuer_id;
    END IF;

    -- Проверка наличия книги в таблице Books
    SELECT EXISTS (SELECT 1 FROM Books WHERE id = p_book_id) INTO book_exists;

    IF NOT book_exists THEN
        RAISE EXCEPTION 'Book with ID % does not exist.', p_book_id;
    END IF;

    -- Добавление записи в таблицу BookDistribution
    INSERT INTO BookDistribution (book_id, user_id, issuer_id, issue_date, return_date)
    VALUES (p_book_id, p_user_id, p_issuer_id, p_issue_date, p_return_date);

    RAISE NOTICE 'Book issued by librarian ID % to user ID % for book ID %.', p_issuer_id, p_user_id, p_book_id;
END;
$$;

-- для добавления записей в Reviews
CREATE OR REPLACE PROCEDURE add_review(
    p_user_id INT,
    p_book_id INT,
    p_content TEXT,
    p_rating INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    reviewer_status BOOLEAN;
BEGIN
    -- Проверка, является ли пользователь рецензентом
    SELECT is_reviewer INTO reviewer_status
    FROM Users
    WHERE id = p_user_id;

    IF NOT reviewer_status THEN
        RAISE EXCEPTION 'User with ID % is not a reviewer.', p_user_id;
    END IF;

    -- Добавление записи в таблицу Reviews
    INSERT INTO Reviews (user_id, book_id, content, rating, created_at)
    VALUES (p_user_id, p_book_id, p_content, p_rating, NOW());
END;
$$;



