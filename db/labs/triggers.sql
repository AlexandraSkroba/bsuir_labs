--ТРИГГЕР ДЛЯ ЛОГОВ
CREATE OR REPLACE FUNCTION log_user()
RETURNS TRIGGER AS $$
BEGIN
    insert into user_activity(user_id, activity_type, date)
    VALUES (NEW.id, 'Action', now());
    RETURN new;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER log_user
AFTER INSERT OR UPDATE ON users
FOR EACH ROW
EXECUTE FUNCTION log_user();
--==========================================================================

--ТРИГГЕР ДЛЯ СОЗДАНИЯ НОВОГО ПРОФИЛЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ
CREATE OR REPLACE FUNCTION create_profile_for_new_user()
RETURNS TRIGGER AS $$
BEGIN
    IF NOT EXISTS (SELECT * FROM profile WHERE user_id = NEW.id) THEN
        INSERT INTO profile (user_id, name, biography, date_of_birth, gender)
        VALUES (NEW.id, NEW.username, NULL, NULL, NULL);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS create_profile_for_new_user ON users;
CREATE TRIGGER trigger_create_user_profile
AFTER INSERT
ON users
FOR EACH ROW
EXECUTE FUNCTION create_profile_for_new_user();
--=================================================================================================

--ТРИГГЕР ДЛЯ УДАЛЕНИЯ ПОЛЬЗОВАТЕЛЯ И ПРОФИЛЯ
CREATE OR REPLACE FUNCTION delete_user()
RETURNS TRIGGER AS $$
BEGIN
    DELETE FROM profile WHERE user_id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trigger_delete_user ON users;
CREATE TRIGGER trigger_delete_user
BEFORE DELETE ON users
FOR EACH ROW
EXECUTE FUNCTION delete_user();
--================================================================


--ЗАПРОСЫ ДЛЯ ПРОВЕРКИ
select * from user_activity order by id desc;
select * from users;

INSERT INTO users (username, email, password, role_id)
VALUES ('новый_пользователь', 'новый_почтовый_адрес@example.com', 'пароль', 1);

DELETE FROM users WHERE id = 13;

SELECT
    users.id as user_id,
    users.username,
    profile.name,
    profile.date_of_birth
FROM users
LEFT JOIN profile ON users.id = profile.user_id
order by user_id desc;
