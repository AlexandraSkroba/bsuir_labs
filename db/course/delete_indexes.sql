DROP INDEX IF EXISTS idx_users_email;
DROP INDEX IF EXISTS idx_users_username;
DROP INDEX IF EXISTS idx_books_title;
DROP INDEX IF EXISTS idx_books_isbn;
DROP INDEX IF EXISTS idx_attendance_user_id;
DROP INDEX IF EXISTS idx_attendance_timestamp;
DROP INDEX IF EXISTS idx_attendance_timestamp_brin;
DROP INDEX IF EXISTS idx_reservations_user_id;
DROP INDEX IF EXISTS idx_reservations_book_id;
DROP INDEX IF EXISTS idx_reservations_status;
DROP INDEX IF EXISTS idx_reviews_book_id;
DROP INDEX IF EXISTS idx_reviews_user_id;
DROP INDEX IF EXISTS idx_notifications_user_id;
DROP INDEX IF EXISTS idx_notifications_read_status;
DROP INDEX IF EXISTS idx_notifications_status_time;
DROP INDEX IF EXISTS idx_events_branch_id;
DROP INDEX IF EXISTS idx_events_start_time;
DROP INDEX IF EXISTS idx_events_branch_time;
DROP INDEX IF EXISTS idx_bookdistribution_user_id;
DROP INDEX IF EXISTS idx_bookdistribution_book_id;
DROP INDEX IF EXISTS idx_bookdistribution_issue_date;
DROP INDEX IF EXISTS idx_feedbacks_content;
DROP INDEX IF EXISTS idx_ebooks_file_format_language;
DROP INDEX IF EXISTS idx_books_author_category;
