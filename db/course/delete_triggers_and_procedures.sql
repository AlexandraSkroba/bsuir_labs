DROP TRIGGER IF EXISTS trigger_update_copies ON BookDistribution;
DROP FUNCTION IF EXISTS update_copies_available();

DROP TRIGGER IF EXISTS trigger_add_fine ON BookDistribution;
DROP FUNCTION IF EXISTS add_fine_for_overdue_books();

DROP TRIGGER IF EXISTS trigger_notify_reservation ON Reservations;
DROP FUNCTION IF EXISTS notify_reservation();

DROP TRIGGER IF EXISTS trigger_update_reviewer_status ON CriticApplications;
DROP FUNCTION IF EXISTS update_reviewer_status();

DROP TRIGGER IF EXISTS trigger_update_feedback_rating ON FeedbackRatings;
DROP FUNCTION IF EXISTS update_feedback_rating();

DROP TRIGGER IF EXISTS trigger_log_reservations ON Reservations;
DROP TRIGGER IF EXISTS trigger_log_reviews ON Reviews;
DROP FUNCTION IF EXISTS log_user_activity() CASCADE;

DROP TRIGGER IF EXISTS trigger_create_profile ON Users;
DROP FUNCTION IF EXISTS create_profile_for_user();

DROP TRIGGER IF EXISTS trigger_delete_expired_reservations ON Reservations;
DROP FUNCTION IF EXISTS delete_expired_reservations();

DROP PROCEDURE IF EXISTS reserve_book(INT, INT);
DROP PROCEDURE IF EXISTS add_user(VARCHAR, VARCHAR, VARCHAR);
DROP PROCEDURE IF EXISTS add_book_with_branch(VARCHAR, INT, INT, INT, varchar, varchar, INT, INT, INT);
DROP PROCEDURE IF EXISTS add_book_distribution(INT, INT, INT, timestamp, timestamp);
drop procedure if exists add_book_distribution(int, int, int, timestamp with time zone,timestamp with time zone);
drop procedure if exists add_review(int, int, text, int);
drop procedure if exists add_book_with_branch (varchar, int, int[], int, varchar, varchar, int, int, int)