AMALGA=sh dev/etc/amalgamate_file.sh
AMALGL=sh dev/etc/amalgamate_file_literally.sh
ETCDIR=dev/etc/
INCDIR=dev/include/octaspire/core/
SRCDIR=dev/src/
TESTDR=dev/test/
EXTDIR=dev/external/
DOTDIR=$(EXTDIR)octaspire_dotfiles/
DEVDOCDIR=dev/doc/
RELDIR=release/
RELDOCDIR=$(RELDIR)documentation/
AMALGAMATION=$(RELDIR)octaspire-core-amalgamated.c
UNAME=$(shell uname -s)
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g -O2
LDFLAGS=-lm

DOCEXAMPLES += $(wildcard $(DEVDOCDIR)book/examples/sh/*.sh)
DOCEXAMPLES += $(wildcard $(DEVDOCDIR)book/examples/c/*.c)
DOCEXAMPLES += $(wildcard $(RELDIR)examples/*.c)

TESTOBJS := $(TESTDR)test.o              \
            $(TESTDR)test_helpers.o      \
            $(TESTDR)test_input.o        \
            $(TESTDR)test_list.o         \
            $(TESTDR)test_map.o          \
            $(TESTDR)test_memory.o       \
            $(TESTDR)test_pair.o         \
            $(TESTDR)test_queue.o        \
            $(TESTDR)test_stdio.o        \
            $(TESTDR)test_string.o       \
            $(TESTDR)test_utf8.o         \
            $(TESTDR)test_vector.o       \
            $(TESTDR)test_semver.o

.PHONY: development submodules-init submodules-pull clean codestyle cppcheck valgrind test coverage major minor patch push


all: development

###############################################################################
####### Development part: build using separate implementation files ###########
###############################################################################

development: octaspire-core-unit-test-runner

octaspire-core-unit-test-runner: $(TESTOBJS) $(EXTDIR)jenkins_one_at_a_time.o
	$(info LD  $@)
	@$(CC) $(CFLAGS) $(TESTOBJS) $(EXTDIR)jenkins_one_at_a_time.o -o $@ $(LDFLAGS)

$(TESTDR)test.o: $(TESTDR)test.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_helpers.o: $(TESTDR)test_helpers.c $(SRCDIR)octaspire_helpers.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_input.o: $(TESTDR)test_input.c $(SRCDIR)octaspire_input.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_list.o: $(TESTDR)test_list.c $(SRCDIR)octaspire_list.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_map.o: $(TESTDR)test_map.c $(SRCDIR)octaspire_map.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_memory.o: $(TESTDR)test_memory.c $(SRCDIR)octaspire_memory.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_pair.o: $(TESTDR)test_pair.c $(SRCDIR)octaspire_pair.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_queue.o: $(TESTDR)test_queue.c $(SRCDIR)octaspire_queue.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_stdio.o: $(TESTDR)test_stdio.c $(SRCDIR)octaspire_stdio.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_string.o: $(TESTDR)test_string.c $(SRCDIR)octaspire_string.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_utf8.o: $(TESTDR)test_utf8.c $(SRCDIR)octaspire_utf8.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_vector.o: $(TESTDR)test_vector.c $(SRCDIR)octaspire_vector.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(TESTDR)test_semver.o: $(TESTDR)test_semver.c $(SRCDIR)octaspire_semver.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/include -I dev $< -o $@

$(EXTDIR)jenkins_one_at_a_time.o: $(EXTDIR)jenkins_one_at_a_time.c
	$(info CC  $<)
	@$(CC) $(CFLAGS) -c -I dev/external $< -o $@



###############################################################################
####### Release part: build using amalgamation ################################
###############################################################################

$(RELDIR)octaspire-core-unit-test-runner: $(DOTDIR)LICENSE $(AMALGAMATION)
	@sh $(ETCDIR)build_amalgamation.sh

$(DOTDIR)LICENSE:
	@make submodules-init --silent

submodules-init:
	@echo "Initializing submodules..."
	@git submodule init
	@git submodule update
	@echo "Done."

submodules-pull:
	@echo "Pulling submodules..."
	@git submodule update --recursive --remote
	@make -s TAGS
	@echo "Done."

$(AMALGAMATION): $(ETCDIR)amalgamation_head.c                \
                 $(EXTDIR)jenkins_one_at_a_time.h            \
                 $(INCDIR)octaspire_core_config.h            \
                 $(INCDIR)octaspire_utf8.h                   \
                 $(INCDIR)octaspire_memory.h                 \
                 $(INCDIR)octaspire_vector.h                 \
                 $(INCDIR)octaspire_list.h                   \
                 $(INCDIR)octaspire_queue.h                  \
                 $(INCDIR)octaspire_string.h                 \
                 $(INCDIR)octaspire_pair.h                   \
                 $(INCDIR)octaspire_stdio.h                  \
                 $(INCDIR)octaspire_input.h                  \
                 $(INCDIR)octaspire_map.h                    \
                 $(INCDIR)octaspire_helpers.h                \
                 $(INCDIR)octaspire_semver.h                 \
                 $(ETCDIR)amalgamation_impl_head.c           \
                 $(EXTDIR)jenkins_one_at_a_time.c            \
                 $(SRCDIR)octaspire_memory.c                 \
                 $(SRCDIR)octaspire_helpers.c                \
                 $(SRCDIR)octaspire_utf8.c                   \
                 $(SRCDIR)octaspire_vector.c                 \
                 $(SRCDIR)octaspire_list.c                   \
                 $(SRCDIR)octaspire_queue.c                  \
                 $(SRCDIR)octaspire_string.c                 \
                 $(SRCDIR)octaspire_pair.c                   \
                 $(SRCDIR)octaspire_map.c                    \
                 $(SRCDIR)octaspire_input.c                  \
                 $(SRCDIR)octaspire_stdio.c                  \
                 $(SRCDIR)octaspire_semver.c                 \
                 $(ETCDIR)amalgamation_impl_tail.c           \
                 $(EXTDIR)greatest.h                         \
                 $(TESTDR)test_helpers.c                     \
                 $(TESTDR)test_utf8.c                        \
                 $(TESTDR)test_semver.c                      \
                 $(TESTDR)test_memory.c                      \
                 $(TESTDR)test_stdio.c                       \
                 $(TESTDR)test_input.c                       \
                 $(TESTDR)test_vector.c                      \
                 $(TESTDR)test_list.c                        \
                 $(TESTDR)test_queue.c                       \
                 $(TESTDR)test_string.c                      \
                 $(TESTDR)test_pair.c                        \
                 $(TESTDR)test_map.c                         \
                 $(ETCDIR)amalgamation_impl_unit_test_tail.c
	@echo "Creating amalgamation..."
	@rm -rf $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_head.c                $(AMALGAMATION)
	@$(AMALGA) $(EXTDIR)jenkins_one_at_a_time.h            $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_core_config.h            $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_utf8.h                   $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_memory.h                 $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_vector.h                 $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_list.h                   $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_queue.h                  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_string.h                 $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_pair.h                   $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_stdio.h                  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_input.h                  $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_map.h                    $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_helpers.h                $(AMALGAMATION)
	@$(AMALGA) $(INCDIR)octaspire_semver.h                 $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_head.c           $(AMALGAMATION)
	@$(AMALGA) $(EXTDIR)jenkins_one_at_a_time.c            $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_memory.c                 $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_helpers.c                $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_utf8.c                   $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_vector.c                 $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_list.c                   $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_queue.c                  $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_string.c                 $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_pair.c                   $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_map.c                    $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_input.c                  $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_stdio.c                  $(AMALGAMATION)
	@$(AMALGA) $(SRCDIR)octaspire_semver.c                 $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_tail.c           $(AMALGAMATION)
	@$(AMALGL) $(EXTDIR)greatest.h                         $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_helpers.c                     $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_utf8.c                        $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_memory.c                      $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_stdio.c                       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_input.c                       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_vector.c                      $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_list.c                        $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_queue.c                       $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_string.c                      $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_pair.c                        $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_map.c                         $(AMALGAMATION)
	@$(AMALGA) $(TESTDR)test_semver.c                      $(AMALGAMATION)
	@$(AMALGL) $(ETCDIR)amalgamation_impl_unit_test_tail.c $(AMALGAMATION)

$(RELDOCDIR)core-manual.html: $(DEVDOCDIR)book/core-manual.htm $(DOCEXAMPLES)
	$(info Generate $@)
	@python2 $(DEVDOCDIR)book/build_book.py $< > $@

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
                octaspire_stdio_fread_test                                            \
                $(RELDIR)example                                                      \
                $(RELDIR)octaspire_helpers_path_to_buffer_failure_on_empty_file_test  \
                $(RELDIR)octaspire_helpers_path_to_buffer_test                        \
                $(RELDIR)octaspire_input_new_from_path_test                           \
                $(RELDIR)octaspire_stdio_fread_test                                   \
                $(SRCDIR)*.o                                                          \
                $(TESTDR)*.o                                                          \
                $(EXTDIR)*.o                                                          \
                octaspire-core-unit-test-runner                                       \
                $(DEVDOCDIR)book/examples/sh/*.html                                   \
                $(DEVDOCDIR)book/examples/c/*.html                                    \
                $(DEVDOCDIR)book/examples/dern/*.html                                 \
                $(RELDIR)examples/*.html

codestyle:
	@vera++ --root dev/external/vera --profile octaspire --error $(wildcard $(SRCDIR)*.[ch])

cppcheck:
	@cppcheck --std=c99 -I dev/include --enable=warning,performance,portability --verbose --quiet $(wildcard $(SRCDIR)*.[ch])

valgrind: $(RELDIR)octaspire-core-unit-test-runner
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $(RELDIR)octaspire-core-unit-test-runner --write-test-files

test: $(RELDIR)octaspire-core-unit-test-runner
	@$(RELDIR)octaspire-core-unit-test-runner --write-test-files

coverage: $(AMALGAMATION)
	@sh $(ETCDIR)build_amalgamation.sh "gcc --coverage"
	@$(RELDIR)/octaspire-core-unit-test-runner --write-test-files
	@lcov --no-external --capture --directory release --output-file $(RELDIR)coverage.info
	@genhtml $(RELDIR)coverage.info --output-directory coverage
	@xdg-open coverage/index.html &

TAGS: $(SRCDIR)*.c $(INCDIR)*.h
	@etags -o $@ $^

major:
	@sh dev/etc/bump-version.sh major
	@make -s TAGS
	@echo "Done."

minor:
	@sh dev/etc/bump-version.sh minor
	@make -s TAGS
	@echo "Done."

patch:
	@sh dev/etc/bump-version.sh patch
	@make -s TAGS
	@echo "Done."

push:
	@git push origin-gitlab
	@git push origin-bitbucket
	@git push origin-sr
	@git push origin-github
