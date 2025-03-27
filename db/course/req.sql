DO $$
BEGIN
    CALL add_book_distribution(1, 3, 11, NOW(), NOW() + INTERVAL '14 days');
    CALL add_book_distribution(2, 4, 12, NOW() - INTERVAL '2 days', NOW() + INTERVAL '12 days');
    CALL add_book_distribution(3, 5, 11, NOW() - INTERVAL '1 week', NOW() + INTERVAL '7 days');
    CALL add_book_distribution(4, 6, 12, NOW() - INTERVAL '5 days', NOW() + INTERVAL '9 days');
    CALL add_book_distribution(5, 7, 11, NOW() - INTERVAL '3 days', NOW() + INTERVAL '11 days');
END;
$$ LANGUAGE plpgsql;
select * from bookbranch;
-- delete from bookdistribution where id=5;

select * from books;
select * from bookbranch;
select * from categories;
select * from bookcategories;
--DELETE FROM Books WHERE id = 1;

UPDATE CriticApplications
SET status = 'approved'
WHERE id = 3;
select * from criticapplications;
select * from users;

--- CALL add_review(3, 1, 'Очень глубокая книга, рекомендую к прочтению.', 5);
CALL add_review(5, 3, 'Превосходный стиль автора, книга читается на одном дыхании.', 5);
select * from reviews;

select * from users;
select * from useractivity order by id desc;
-- update users
-- set username = 'blabla'
-- where id = 1

delete from users where id = 1;
