--SELECT
SELECT * FROM profile WHERE gender = 'F';

SELECT DISTINCT activity_type
    FROM user_activity ORDER BY activity_type;

SELECT DISTINCT activity_type
    FROM user_activity ORDER BY activity_type DESC;

SELECT * FROM user_activity LIMIT 5;

SELECT * FROM user_activity OFFSET 5 LIMIT 3;

SELECT * FROM profile
WHERE date_of_birth > '1992-02-02';

SELECT * from profile
where user_id in (1,4,5);

SELECT max(user_id) from profile;

SELECT * from profile
where user_id BETWEEN 1 AND 3;

SELECT avg(user_id) as avggrade from profile;

select * from users
where password like '%3';

select * from users
where username ilike 'q%';

--UPDATE
UPDATE profile
SET biography = NULL
WHERE biography = '';

UPDATE roles
SET role_name = 'Writer'
WHERE role_name = 'User';

UPDATE articles
SET content = 'Updated content'
WHERE title = 'Web Development Best Practices';

--DELETE / DROP
DROP TYPE gender;

--ALTER TABLE profile
--DROP COLUMN links;

DELETE FROM articles
WHERE title = 'Introduction to SQL';

DELETE FROM comments
WHERE user_id = (SELECT id FROM users WHERE username = 'admin');

--ALTER
ALTER TABLE profile
ALTER COLUMN gender TYPE gender USING gender::gender;

ALTER TABLE profile
ADD COLUMN age INT;

ALTER TABLE profile
DROP COLUMN age;


SELECT * FROM profile;
SELECT DISTINCT gender
    FROM profile ORDER BY gender DESC;


--ВЫЗОВ ПРОЦЕДУРЫ
CALL UpdateArticleTitle('Название статьи', 'Новое название статьи');
SELECT articles.id, articles.title FROM articles ORDER BY articles.id DESC;

select * from profile order by id desc;
select * from  users
join roles on users.role_id = roles.id
order by users.id desc;

select * from articles order by id;

(SELECT name, table1.title
FROM
(SELECT articles.title, users.username, users.id
FROM articles
JOIN users ON articles.author_id = users.id) AS table1
JOIN profile ON table1.id = profile.user_id);

SELECT articles.id AS article_id, articles.title, COUNT(ratings.id) AS likes
FROM articles
LEFT JOIN ratings ON articles.id = ratings.article_id
GROUP BY articles.id, articles.title
order by article_id;

SELECT comment_text
FROM comments
left join ratings on comments.id = ratings.comment_id;

SELECT
    u.username,
    a.title,
    a.content
FROM
    users u
JOIN
    favorites f ON u.id = f.user_id
JOIN
    articles a ON f.article_id = a.id
order by username;

SELECT ua.id AS activity_id, u.username, ua.activity_type, ua.date
FROM user_activity ua
JOIN users u ON ua.user_id = u.id;

