;;   ------------------ 6.1.l ------------------
;;
;;				created by: parker johnson
;;				date completed: sept 17 4:00 a.m.
;;
;;   HONOR PLEDGE:
;;		    I, parker johnson, pledge that this and confirms
;;		    to SPCA.
;;					parker johnson
;;
;;-------------------------------------------------

;6-1  find-book-bytitle-words program finds book titles using subsetp

(defun book-title (book)
  (first book))

(defun find-book-bytitle-words (words books)
   (cond ((endp books) nil)
         ((subsetp words (second (book-title (first books)))) (first books))
	 (t (find-book-bytitle-words words (rest books)))))

(defun make-book (title author classification)
   (list (list 'title title)
	 (list 'author author)
	 (list 'classification classification)))

(setf books
  (list
     (make-book '(artificial intelligence)
		'(patrick henry winston)
		'(technical ai))
     (make-book '(common lisp)
		'(guy l steele)
		'(technical lisp))
     (make-book '(moby dick)
		'(herman melville)
		'(fiction))
     (make-book '(tom sawyer)
		'(mark twain)
		'(fiction))
     (make-book '(the black orchid)
		'(rex stout)
		'(fiction mystery))))

;sample input:
;(find-book-bytitle-words '(artificial) books)
;(find-book-bytitle-words '(intelligence) books)
;(find-book-bytitle-words '(orchid) books)
;(find-book-bytitle-words '(black orchid) books)
;(find-book-bytitle-words '(blue orchid) books)

