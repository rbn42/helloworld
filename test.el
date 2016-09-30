(princ "Hello world!  I'm writing to STDOUT but I'm not in quotes!\n")
(princ 2 )
(princ "\n")
(+ 2 2)
(print 3)

(print
  (+ 3 (+ 1 2))
  )

(setq my-name "Bastien")

(defun p (x) 
  (progn 
    (princ x)
    (princ "\n")))
(p 3)
(p my-name)
(defun a (a b) (+ a b))
(p (a 3 4))

(defun get-string-from-file (filePath)
  "Return filePath's file content."
  (with-temp-buffer
    (insert-file-contents filePath)
    (buffer-string)))
;; thanks to “Pascal J Bourguignon” and “TheFlyingDutchman 〔zzbba…@aol.com〕”. 2010-09-02
(defun read-lines (filePath)
  "Return a list of lines of a file at filePath."
  (with-temp-buffer
    (insert-file-contents filePath)
    (split-string (buffer-string) "\n" t)))

(p (get-string-from-file "./file"))
(p (read-lines "./file"))
(p (read-lines "./file_cal"))
(princ mode-line-modified)
(princ mode-line-end-spaces)
(setq a '(%1* %1+))
(princ a)
