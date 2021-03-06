

SUBDIRS=src tests interfaces
DOC_FILES = 	$(top_builddir)/doc/book/Makefile.in \
	$(top_builddir)/doc/igraph.info \
	$(top_srcdir)/doc/Makefile.in \
	$(top_srcdir)/doc/igraph.3

pkgconfigdir = @libdir@/pkgconfig
pkgconfig_DATA = igraph.pc

EXTRA_DIST = igraph.pc $(top_srcdir)/include/* $(DOC_FILES) \
	examples $(top_srcdir)/interfaces/R/Makefile.in \
	$(top_srcdir)/interfaces/R/DESCRIPTION.in \
	$(top_srcdir)/interfaces/R/configure.in.in

install-exec-hook:
	if test -f $(top_builddir)/src/.libs/cygigraph-0.dll ; \
		then cp $(top_builddir)/src/.libs/cygigraph-0.dll \
		$(DESTDIR)$(libdir) ; fi

install-info:
	if test -f doc/igraph.info; then d="doc"; \
         else d=$(srcdir); fi; \
        $(INSTALL_DATA) $$d/igraph.info $(infodir); \
        if $(SHELL) -c 'install-info --version' \
           >/dev/null 2>&1; then \
          install-info --infodir=$(infodir) $$d/igraph.info; \
        else true; fi

dist-hook:
	rm -rf `find $(distdir)/examples -type d -name .arch-ids`

MAINTAINERCLEANFILES = Makefile.in

## to make sure make doc will always call doxygen rule
## and deb will generate Debian packages
.PHONY: framework msvc

framework: all
	rm -rf $(top_builddir)/igraph.framework
	mkdir -p $(top_builddir)/igraph.framework/Versions/$(VERSION)/Headers
	mkdir -p $(top_builddir)/igraph.framework/Versions/$(VERSION)/Resources
	ln -s $(VERSION) $(top_builddir)/igraph.framework/Versions/Current
	ln -s Versions/Current/Headers $(top_builddir)/igraph.framework/Headers
	ln -s Versions/Current/Resources $(top_builddir)/igraph.framework/Resources
	cp $(top_srcdir)/include/* $(top_builddir)/igraph.framework/Headers/
	cp $(top_builddir)/src/.libs/libigraph.dylib $(top_builddir)/igraph.framework/Versions/Current/igraph
	ln -s Versions/Current/igraph $(top_builddir)/igraph.framework/igraph
	cp $(top_builddir)/igraph_Info.plist $(top_builddir)/igraph.framework/Versions/Current/Resources/Info.plist

test: all
	for i in interfaces/*; do \
		if [ -x $$i/test.sh ]; then \
		  $$i/test.sh; \
	 	fi; \
	done

msvc: all
	rm -rf $(top_builddir)/igraph-$(VERSION)-msvc
	mkdir $(top_builddir)/igraph-$(VERSION)-msvc
	cp -r src $(top_builddir)/igraph-$(VERSION)-msvc/
	rm -rf $(top_builddir)/igraph-$(VERSION)-msvc/src/{.deps,.libs}
	rm -rf $(top_builddir)/igraph-$(VERSION)-msvc/src/config.h
	rm -rf $(top_builddir)/igraph-$(VERSION)-msvc/src/*.{o,lo}
	cp -r msvc/include $(top_builddir)/igraph-$(VERSION)-msvc/winclude
	mkdir $(top_builddir)/igraph-$(VERSION)-msvc/winlib
	cp msvc/igraph.{sln,vcproj} $(top_builddir)/igraph-$(VERSION)-msvc/
	cp -r msvc/igraphtest .
	rm -rf igraph-$(VERSION)-msvc.zip
	zip -r igraph-$(VERSION)-msvc.zip igraph-$(VERSION)-msvc igraphtest

CLEANFILES=
