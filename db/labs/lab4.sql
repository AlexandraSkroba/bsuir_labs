-- User and Rating
SELECT *
FROM users
INNER JOIN ratings ON users.id = ratings.user_id;

SELECT author_id, count(*)
FROM articles
GROUP BY author_id;

SELECT username
FROM ( SELECT author_id, count(*) AS comments
FROM articles
INNER JOIN comments on articles.id = comments.article_id
GROUP BY author_id
HAVING count(*) > 2 ) AS Table2
inner join users on Table2.author_id = users.id;

SELECT username, title, published_at
FROM
( SELECT author_id, title, published_at, rank() OVER (PARTITION BY author_id ORDER BY published_at) as DateRank
FROM articles ) AS Table1
INNER JOIN users ON Table1.author_id = users.id
where DateRank = 1;

INSERT INTO comments (user_id, article_id, comment_text, comment_date)
VALUES (2, 4, 'Супер Кул!', '2023-01-03 08:45:00');

SELECT users.username, articles.title
FROM users
LEFT JOIN articles ON users.id = articles.author_id;

SELECT articles.title, comments.comment_text
FROM articles
RIGHT JOIN comments ON articles.id = comments.article_id;

SELECT users.username, comments.comment_text
FROM users
FULL JOIN comments ON users.id = comments.user_id;

SELECT users.username, articles.title
FROM users
CROSS JOIN articles;

SELECT u1.username AS user1, u2.username AS user2
FROM users u1
JOIN users u2 ON u1.id <> u2.id;

SELECT role_id, COUNT(*) as user_count
FROM users
GROUP BY role_id
HAVING COUNT(*) > 1;

SELECT username
FROM users u
WHERE EXISTS (SELECT 1 FROM articles a WHERE a.author_id = u.id);

-- INSERT INTO backup_users (username, email, role_id)
-- SELECT username, email, role_id
-- FROM users
-- WHERE role_id = 2;

SELECT username,
       CASE
          WHEN role_id = 1 THEN 'Admin'
          WHEN role_id = 2 THEN 'Writer'
          ELSE 'Reader'
       END as user_role
FROM users;

EXPLAIN SELECT username FROM users WHERE role_id = 2;

EXPLAIN ANALYSE SELECT username FROM users WHERE role_id = 2;


--username, самая популярный тег статьи

SELECT table2.username, tags.tag_name, COUNT(*) as tag_count
FROM
  (SELECT table1.username, table1.title, table1.user_id, articles_tags.tag_id
   FROM
     (SELECT users.id AS user_id, users.username, articles.*
      FROM users
      INNER JOIN articles ON users.id = articles.author_id) AS table1
   INNER JOIN articles_tags ON table1.id = articles_tags.article_id) AS table2
INNER JOIN tags ON table2.tag_id = tags.id
GROUP BY table2.username, tags.tag_name;


SELECT username, tag_name, tag_count
FROM
  ( SELECT table2.username, tags.tag_name, COUNT(*) AS tag_count, RANK() OVER (PARTITION BY table2.username ORDER BY COUNT(*) DESC) AS rnk
  FROM
    (SELECT table1.username, table1.user_id, articles_tags.tag_id
     FROM
       (SELECT users.id AS user_id, users.username, articles.id
        FROM users
        INNER JOIN articles ON users.id = articles.author_id) AS table1
     INNER JOIN articles_tags ON table1.id = articles_tags.article_id) AS table2
  INNER JOIN tags ON table2.tag_id = tags.id
  GROUP BY table2.username, tags.tag_name
) AS table3
WHERE rnk = 1;

