AMALGA=sh dev/etc/amalgamate_file.sh
AMALGL=sh dev/etc/amalgamate_file_literally.sh
ETCDIR=dev/etc/
INCDIR=dev/include/octaspire/core/
SRCDIR=dev/src/
TESTDR=dev/test/
EXTDIR=dev/external/
DEVDOCDIR=dev/doc/
RELDIR=release/
RELDOCDIR=$(RELDIR)documentation/
AMALGAMATION=$(RELDIR)octaspire-core-amalgamated.c
UNAME=$(shell uname -s)

# In batch mode Emacs doesn't load the usual initialization file. To get the correct
# settings and styles in the batch mode, the initialization file must be loaded manually.
# However, there are still some small problems with the Org export when running in batch
# mode using the default version of Org mode, so the export is run without batch mode at
# the moment.
#EMACSFLAGS=--load dev/external/octaspire_dotfiles/emacs/.emacs.d/init.el --batch
EMACSFLAGS=

.PHONY: clean codestyle cppcheck valgrind test coverage

$(RELDIR)octaspire-core-unit-test-runner: $(AMALGAMATION)
	@echo "Building for $(UNAME)..."
	@if [ "$(UNAME)" = "Linux" ]; then\
            cd release && sh how-to-build/linux.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Darwin" ]; then\
            cd release && sh how-to-build/macOS.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "OpenBSD" ]; then\
            cd release && sh how-to-build/OpenBSD.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "FreeBSD" ]; then\
            cd release && sh how-to-build/FreeBSD.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "NetBSD" ]; then\
            cd release && sh how-to-build/NetBSD.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Minix" ]; then\
            cd release && sh how-to-build/minix3.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "DragonFly" ]; then\
            cd release && sh how-to-build/DragonFlyBSD.sh > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Haiku" ]; then\
            cd release && sh how-to-build/haiku.sh > /dev/null 2>&1 && echo "Done.";\
        else\
            echo "This platform is not handled by Makefile at the moment. Please build using a script from 'release/how-to-build'.";\
        fi;

$(AMALGAMATION): $(ETCDIR)amalgamation_head.c                \
                 $(EXTDIR)jenkins_one_at_a_time.h            \
                 $(INCDIR)octaspire_core_config.h            \
                 $(INCDIR)octaspire_utf8.h                   \
                 $(INCDIR)octaspire_memory.h                 \
                 $(INCDIR)octaspire_container_vector.h       \
                 $(INCDIR)octaspire_container_list.h         \
                 $(INCDIR)octaspire_container_queue.h        \
                 $(INCDIR)octaspire_container_utf8_string.h  \
                 $(INCDIR)octaspire_container_pair.h         \
                 $(INCDIR)octaspire_stdio.h                  \
                 $(INCDIR)octaspire_input.h                  \
                 $(INCDIR)octaspire_container_hash_map.h     \
                 $(INCDIR)octaspire_helpers.h                \
                 $(ETCDIR)amalgamation_impl_head.c           \
                 $(EXTDIR)jenkins_one_at_a_time.c            \
                 $(SRCDIR)octaspire_memory.c                 \
                 $(SRCDIR)octaspire_helpers.c                \
                 $(SRCDIR)octaspire_utf8.c                   \
                 $(SRCDIR)octaspire_container_vector.c       \
                 $(SRCDIR)octaspire_container_list.c         \
                 $(SRCDIR)octaspire_container_queue.c        \
                 $(SRCDIR)octaspire_container_utf8_string.c  \
                 $(SRCDIR)octaspire_container_pair.c         \
                 $(SRCDIR)octaspire_container_hash_map.c     \
                 $(SRCDIR)octaspire_input.c                  \
                 $(SRCDIR)octaspire_stdio.c                  \
                 $(ETCDIR)amalgamation_impl_tail.c           \
                 $(EXTDIR)greatest.h                         \
                 $(TESTDR)test_helpers.c                     \
                 $(TESTDR)test_utf8.c                        \
                 $(TESTDR)test_memory.c                      \
                 $(TESTDR)test_stdio.c                       \
                 $(TESTDR)test_input.c                       \
                 $(TESTDR)test_container_vector.c            \
                 $(TESTDR)test_container_list.c              \
                 $(TESTDR)test_container_queue.c             \
                 $(TESTDR)test_container_utf8_string.c       \
                 $(TESTDR)test_container_pair.c              \
                 $(TESTDR)test_container_hash_map.c          \
                 $(ETCDIR)amalgamation_impl_unit_test_tail.c
	@echo "Creating amalgamation..."
	@rm -rf $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_head.c                $(AMALGAMATION)
	@$(AMALGA) $(EXTDIR)jenkins_one_at_a_time.h            $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_core_config.h            $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_utf8.h                   $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_memory.h                 $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_vector.h       $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_list.h         $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_queue.h        $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_utf8_string.h  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_pair.h         $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_stdio.h                  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_input.h                  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_container_hash_map.h     $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_helpers.h                $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_head.c           $(AMALGAMATION)
	@$(AMALGA) $(EXTDIR)jenkins_one_at_a_time.c            $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_memory.c                 $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_helpers.c                $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_utf8.c                   $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_vector.c       $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_list.c         $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_queue.c        $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_utf8_string.c  $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_pair.c         $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_container_hash_map.c     $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_input.c                  $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_stdio.c                  $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_tail.c           $(AMALGAMATION)
	@$(AMALGL) $(EXTDIR)greatest.h                         $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_helpers.c                     $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_utf8.c                        $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_memory.c                      $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_stdio.c                       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_input.c                       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_vector.c            $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_list.c              $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_queue.c             $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_utf8_string.c       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_pair.c              $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_container_hash_map.c          $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_unit_test_tail.c $(AMALGAMATION)

$(RELDOCDIR)core-manual.html: $(DEVDOCDIR)book/core-manual.org
	@LANG=eng_US.utf8 emacs $(EMACSFLAGS) $< --funcall org-reload --funcall org-html-export-to-html --kill > /dev/null 2>&1
	@mv dev/doc/book/core-manual.html release/documentation/

clean:
	@rm -rf $(AMALGAMATION)                                                       \
                $(RELDIR)octaspire-core-unit-test-runner                              \
                $(RELDIR)coverage.info                                                \
                $(RELDIR)octaspire-core-amalgamated.gcda                              \
                $(RELDIR)octaspire-core-amalgamated.gcno                              \
                coverage                                                              \
                $(RELDIR)hash-map-example                                             \
                $(RELDIR)string-example                                               \
                $(RELDIR)vector-example                                               \
                octaspire_helpers_path_to_buffer_failure_on_empty_file_test           \
                octaspire_helpers_path_to_buffer_test                                 \
                octaspire_input_new_from_path_test                                    \
                octaspire_stdio_fread_test

codestyle:
	@vera++ --root dev/external/vera --profile octaspire --error $(wildcard $(SRCDIR)*.[ch])

cppcheck:
	@cppcheck --std=c99 -I dev/include --enable=warning,performance,portability --verbose --quiet $(wildcard $(SRCDIR)*.[ch])

valgrind: $(RELDIR)octaspire-core-unit-test-runner
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $(RELDIR)octaspire-core-unit-test-runner --write-test-files

test: $(RELDIR)octaspire-core-unit-test-runner
	@$(RELDIR)octaspire-core-unit-test-runner --write-test-files

coverage: $(AMALGAMATION)
	@echo "Building for $(UNAME) with coverage enabled..."
	@if [ "$(UNAME)" = "Linux" ]; then\
            cd release && sh how-to-build/linux.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Darwin" ]; then\
            cd release && sh how-to-build/macOS.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "OpenBSD" ]; then\
            cd release && sh how-to-build/OpenBSD.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "FreeBSD" ]; then\
            cd release && sh how-to-build/FreeBSD.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "NetBSD" ]; then\
            cd release && sh how-to-build/NetBSD.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Minix" ]; then\
            cd release && sh how-to-build/minix3.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "DragonFly" ]; then\
            cd release && sh how-to-build/DragonFlyBSD.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        elif [ "$(UNAME)" = "Haiku" ]; then\
            cd release && sh how-to-build/haiku.sh gcc --coverage > /dev/null 2>&1 && echo "Done.";\
        else\
            echo "This platform is not handled by Makefile at the moment. Please build using a script from 'release/how-to-build'.";\
        fi;
	@$(RELDIR)/octaspire-core-unit-test-runner --write-test-files
	@lcov --no-external --capture --directory release --output-file $(RELDIR)coverage.info
	@genhtml $(RELDIR)coverage.info --output-directory coverage
	@xdg-open coverage/index.html &