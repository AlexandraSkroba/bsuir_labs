-- СОЗДАНИЕ ПРОЦЕДУРЫ

-- CREATE PROCEDURE ProductSummary AS
-- BEGIN
--     SELECT ProductName AS Product, Manufacturer, Price
--     FROM Products
-- END;

-- ВЫПОЛНЕНИЕ
-- CALL ProductSummary

-- УДАЛЕНИЕ
-- DROP PROCEDURE ProductSummary
--===========================================================================================

--ПРОЦЕДУРА ДЛЯ ДОБАВЛЕНИЯ СТАТЬИ ПО ИМЕНИ ПОЛЬЗОВАТЕЛЯ
CREATE OR REPLACE PROCEDURE AddArticleByUserName(
    IN p_username VARCHAR(50),
    IN p_title VARCHAR(200),
    IN p_content TEXT,
    IN p_published_at TIMESTAMP
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_author_id INT;
    v_role_id INT;
BEGIN
    SELECT id, role_id INTO v_author_id, v_role_id FROM users WHERE username = p_username;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'User with username % not found', p_username;
    END IF;

    IF v_role_id <> 2 THEN
        RAISE EXCEPTION 'User with username % does not have the required role to add an article', p_username;
    END IF;

    INSERT INTO articles (author_id, title, content, published_at)
    VALUES (v_author_id, p_title, p_content, p_published_at);
END;
$$;

CALL AddArticleByUserName('QuillQuest'::VARCHAR, 'Название статьи4567'::VARCHAR, 'Содержание статьи'::TEXT, NOW()::TIMESTAMP);


SELECT  articles.id, articles.title, users.username, tag_name
FROM articles
    INNER JOIN users ON articles.author_id = users.id
    LEFT JOIN articles_tags ON articles.id = articles_tags.article_id
    LEFT JOIN tags ON articles_tags.tag_id = tags.id
ORDER BY articles.id desc;
--================================================================

--ПРОЦЕДУРА ДЛЯ ДОБАВЛЕНИЯ ТЕГА ПО ИМЕНИ ПОЛЬЗОВАТЕЛЯ И НАЗВАНИЯ СТАТЬИ + ДОБАВЛЕНИЕ ТЕГА
CREATE OR REPLACE PROCEDURE AddTagToArticle(
    IN p_article_title VARCHAR(200),
    IN p_author_username VARCHAR(50),
    IN p_tag_name VARCHAR(50)
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_article_id INT;
    v_author_id INT;
    v_tag_id INT;
BEGIN
    SELECT id INTO v_article_id FROM articles WHERE title = p_article_title;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Article with title % not found', p_article_title;
    END IF;

    SELECT id INTO v_author_id FROM users WHERE username = p_author_username;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'User with username % not found', p_author_username;
    END IF;

    IF v_author_id <> (SELECT author_id FROM articles WHERE id = v_article_id) THEN
        RAISE EXCEPTION 'Author of the article does not match the specified author';
    END IF;

    SELECT id INTO v_tag_id FROM tags WHERE tag_name = p_tag_name;

    IF NOT FOUND THEN
        INSERT INTO tags (tag_name) VALUES (p_tag_name) RETURNING id INTO v_tag_id;
    END IF;

    INSERT INTO articles_tags (article_id, tag_id) VALUES (v_article_id, v_tag_id);
END;
$$;

CALL AddTagToArticle('Introduction to SQL'::VARCHAR, 'ProseForge'::VARCHAR, 'Тег1'::VARCHAR);

SELECT  articles.id, articles.title, users.username, tag_name
FROM articles
    INNER JOIN users ON articles.author_id = users.id
    LEFT JOIN articles_tags ON articles.id = articles_tags.article_id
    LEFT JOIN tags ON articles_tags.tag_id = tags.id
ORDER BY articles.id;
--===========================================================================


--ПРОЦЕДУРА ИЗМЕНЕНИЯ НАЗВАНИЯ СТАТЬИ
CREATE OR REPLACE PROCEDURE UpdateArticleTitle(
    IN p_old_title VARCHAR(200),
    IN p_new_title VARCHAR(200)
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_article_id INT;
BEGIN
    SELECT id INTO v_article_id FROM articles WHERE title = p_old_title;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Article with title % not found', p_old_title;
    END IF;

    UPDATE articles SET title = p_new_title WHERE id = v_article_id;
END;
$$;

-- Пример вызова процедуры
CALL UpdateArticleTitle('Новое название статьи', 'Название статьи');

SELECT articles.id, articles.title FROM articles ORDER BY articles.id DESC;
--====================================================================================================


SELECT articles.id, articles.title, users.username AS author_article, comments.comment_text
FROM comments
JOIN articles ON comments.article_id = articles.id
INNER JOIN users ON articles.author_id = users.id;
