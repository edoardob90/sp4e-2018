(TeX-add-style-hook
 "sujet"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "a4paper" "11pt")))
   (TeX-run-style-hooks
    "latex2e"
    "../td"
    "article"
    "art11"))
 :latex)

