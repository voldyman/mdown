 ;; ((nil . ((eval . (progn
 ;;                   (require 'irony)
 ;;                   (setq irony-cdb-compilation-databases 'build/compile_commands.json))))

 ;;       (c++-mode . ((eval add-hook 'before-save-hook #'clang-format-buffer nil t)
 ;;                   (compile-command "cd build && cmake .. && make")))))

((nil . ((require 'irony)
         (setq irony-cdb-compilation-databases 'build/compile_commands.json)))
 (c++-mode . ((eval . (setq project-root-dir
                            (locate-dominating-file buffer-file-name ".dir-locals.el")))
              (compile-command . (format "cmake -B%sbuild -H%s -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && make -C %s/build"
                                         project-root-dir project-root-dir project-root-dir))
              (eval add-hook 'before-save-hook #'clang-format-buffer nil t))))
