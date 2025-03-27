-- запросы по email и username
CREATE UNIQUE INDEX idx_users_email ON Users USING btree (email);
CREATE INDEX idx_users_username ON Users USING btree (username);

-- поля title и isbn часто используются для поиска или фильтрации
CREATE INDEX idx_books_title ON Books USING btree (title);
CREATE UNIQUE INDEX idx_books_isbn ON Books USING btree (isbn);

-- поля user_id и timestamp используются для отслеживания посещений
CREATE INDEX idx_attendance_user_id ON Attendance USING hash (user_id);
CREATE INDEX idx_attendance_timestamp ON Attendance USING btree (timestamp);

-- для фильтрации по user_id, book_id и статусу
CREATE INDEX idx_reservations_user_id ON Reservations USING hash (user_id);
CREATE INDEX idx_reservations_book_id ON Reservations USING hash (book_id);
CREATE INDEX idx_reservations_status ON Reservations USING btree (status);

-- для поиска рецензий
CREATE INDEX idx_reviews_book_id ON Reviews USING hash (book_id);
CREATE INDEX idx_reviews_user_id ON Reviews USING hash (user_id);

-- user_id и read_status для фильтрации
CREATE INDEX idx_notifications_user_id ON Notifications USING hash (user_id);
CREATE INDEX idx_notifications_read_status ON Notifications USING btree (read_status);

-- часто используются branch_id и start_time
CREATE INDEX idx_events_branch_id ON Events USING hash (branch_id);
CREATE INDEX idx_events_start_time ON Events USING btree (start_time);

-- поля user_id, book_id и issue_date для анализа выдач
CREATE INDEX idx_bookdistribution_user_id ON BookDistribution USING hash (user_id);
CREATE INDEX idx_bookdistribution_book_id ON BookDistribution USING hash (book_id);
CREATE INDEX idx_bookdistribution_issue_date ON BookDistribution USING btree (issue_date);

-- поиск по диапазону дат в Attendance
CREATE INDEX idx_attendance_timestamp_brin ON Attendance USING brin (timestamp);

-- поиск по content в Feedbacks
CREATE INDEX idx_feedbacks_content ON Feedbacks USING gin (to_tsvector('english', content));

-- индекс для EBooks по file_format и language
CREATE INDEX idx_ebooks_file_format_language ON EBooks USING btree (file_format, language);

-- для Notifications с учётом read_status и времени
CREATE INDEX idx_notifications_status_time ON Notifications USING btree (read_status, created_at);

-- для быстрого поиска мероприятий по филиалу и времени
CREATE INDEX idx_events_branch_time ON Events USING btree (branch_id, start_time);
