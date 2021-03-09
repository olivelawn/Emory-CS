;;   ------------------ doctor.l ------------------
;;
;;				created by: parker johnson
;;				date completed: oct 8 10:00 a.m.
;;
;;   HONOR PLEDGE:
;;		    I, parker johnson, pledge that this and confirms
;;		    to SPCA.
;;					parker johnson
;;
;;-------------------------------------------------


(defun youmemap (lst)
  (mapcar (function youme) lst) )
(defun youme (w)
  (cond  ((eq w 'i)    'you)
         ((eq w 'my)   'your)
         ((eq w 'mine) 'yours)
         ((eq w 'me)   'you)
         ((eq w 'you)  'me)
         ((eq w 'your) 'my)
         ((eq w 'yours) 'mine)
         ((eq w 'am)   'are)
                 ((eq w 'myself) 'yourself)
                 ((eq w 'yourself) 'myself)
                 (t w) ) )


(defun  match  (A B)
   (cond
      ((null A)  (null B))
      ((or  (atom A)  (atom B))  nil)
      ((equal  (first A)  (first B))
         (match  (rest A)  (rest B)))
      ((and
            (not (atom (first A)))
            (equal  (length (first A)) 2)
            (eq (caar A)  '?)
            (match (cdr A)  (cdr B)))
         (set (cadar  A)  (car B)) T)
      ((and
            (not (atom (first A)))
            (equal  (length (first A)) 2)
            (eq (caar A)  '*))
         (cond
            ((match (cdr A) B)
               (set (cadar A) nil) t)
            ((and A (match (rest A) (rest B)))
               (set (cadar A) (list (car B))) t)
            ((and A (match A (cdr B)))
               (set (cadar A) (cons (car B) (eval (cadar A))) ) t)
       (t nil))) ))

(defun rand_default ()
		(setf num1 (random 5))
		(cond
		  ((= num1 0) (print '(Dr\.  --What exactly do you mean?)))
		  ((= num1 1) (print '(Dr\.  --What are you trying to say?)))
		  ((= num1 2) (print '(Dr\.  --I'm not sure I understand what you mean please reiterate\.)))
		  ((= num1 3) (print '(Dr\.  --Could you rephrase that please\.)))
		  ((= num1 4) (print '(Dr\.  --What are you trying to tell me?)))))

(defun rand_yupreply ()
		(setf num2 (random 3))
		(cond
		  ((= num2 0) '(DR\. --What happend then?))
		  ((= num2 1) '(DR\. --And what did you do then?))
		  ((= num2 2) '(DR\. --O.K. then what?))))

(defun rand_good ()
		(setf num3 (random 3))
		(cond
		  ((= num3 0) '(DR\. --Great! good to hear\.))
		  ((= num3 1) '(DR\. --Wow I'm glad to hear that\.))
		  ((= num3 2) '(DR\. --Swell!))))


(defun rand_no ()
		(setf num4 (random 2))
		(cond
		  ((= num4 0) '(DR\. --Alright suit youself\.))
		  ((= num4 1) '(DR\. --I think you should leave now\.))))



(defun exit ()
		(print '(DR\. --Thank you for visiting and please speak to my secretary about payment before leaving\.))
		(terpri)
		(return T))

(defun doctor ()
  	    (print '(--- You are going to talk to a psychiatrist\. Type in your statement inside) )
        (terpri)
        (print '(--- parentheses like (i am very sad) or (what do you mean) with all) )
        (terpri)
        (print '(--- characters in lower case\. To say nothing type nothing inside parentheses\.) )
        (terpri)
        (print '(--- Don't use commas\. Don't use parentheses inside the enclosing))
        (terpri)
        (print '(--- parentheses\.  Try to use complete sentences to get better))
        (terpri)
        (print '(--- responses\. Be honest to your doctor\. Don't be shy\. If you get) )
        (terpri)
        (print '(--- frustrated you may type in something like (go to hell) or whatever))
        (terpri)
        (print '(--- you want to say to the doctor\. To terminate type (bye) simply\. ) )
        (terpri)
        (print '(--- CNTRL Z will get you out at any time to the operating system lelevl \. ))
        (terpri)
        (print '(--- --- --- Now the session starts\. Type in your response))
		(terpri)

(loop
	(terpri)
	(terpri)
    (setq s (youmemap (read)))
    (cond ((match '(bye) s) (exit) )
		  ((match '() s) (print '(DR\. --Please speak up I cannot hear you )))
		  ((match '(go to hell (* x)) s) (print '(DR\.  --Please do not be fresh with me...I want to help you...let me help you\.)))
		  ((match '(no) s)  (print (rand_no)))
		  ((or (match '(good) s) (match '(great) s)) (print (rand_good)))
          ((match '(you are (* x)) s) (print (append '(DR\.---please tell me why you are) x)))
		  ((match '(how are me (* x)) s) (print '(DR\. --I am doing alright and yourself?)))
		  ((match '(your (* x) died (* y)) s)  (print (append (append (append '(DR.\. --I'm sorry your) x) '(died) y) '(what happend?))))
          ((match '(you have (* x)) s) (print (append '(DR\.--- how long have you had) x)))
          ((match '(because (* x)) s) (print '(DR\.--- is that really the reason) ))
	      ((match '((* y) are me going (* x)) s) (print (append (append '(Dr\.--- i dont know if) y) '(i am going) x))) 
          ((match '(are me (* x)) s) (print '(Dr\.--- hey you know it\.  ) ) ) 
		  ((match '((* x) exploded (* y)) s) (print (append (append '(DR/. -- ) (append x '(exploded))) (append y '(...really?))))) 
		  ((match '((* x) played (* y)) s) (print (append (append (append '(DR\. --) x) '(played)) (append y '(huh?...did it relieve stress?)))))
		  ((match '(you ate (* x)) s) (print (append (append '(DR\. -- how did the) (list (first x))) '(taste?))))  
		  ((match '(since last (* x)) s) (print (append (append '(Dr\. -- What happend last) x) '(?))))
		  ((and (equal (first s) 'me) (member 'optimistic s)) (print '(DR\. -- I just think you are overly pessimistic)))
		  ((or (match '(yeah) s) (match '(yup) s) (match '(yes) s)) (print (append '(DR\. I see...) (rand_yupreply))))
		  ((or (member 'car s) (member 'cars s)) (print '(DR\. --Sounds like trouble to me.)))
		  ((or (member 'problem s) (member 'problems s)) (print '(DR\. --I know...that is why i am here...how can I help you?)))
		  (t (rand_default)))

) ;end of loop
) ;end of doctor function

;sample input:
;(load "doctor.l")
;(doctor)
;(how are you doc)
;(are you a certified psychiatrist)
;(i got problems doc)
;(i am very sad)
;(i have a guilty conscience)
;(since last saturday)
;(my dog died last saturday afternoon)   
;(bubba exploded because i fed him too much food)
;(yeah)
;(yeah)
;(yeah)
;(i ate frankfurters at the convenience mart)
;(i ate corndogs there too)
;(great)
;(great)
;(good)
;(good)
;(you are a way overly optimistic doctor)
;(you happen to be the most optimistic fellow I have ever known)
;(go to hell doctor)
;(no)  
;(no)  
;(bye)

		  
		  

 



