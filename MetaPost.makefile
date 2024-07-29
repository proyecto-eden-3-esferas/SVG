SVGDIR = ../SVG/

copy_to_SVG:
	#cp --update *.mp $(SVGDIR)
	cp makefile $(SVGDIR)MetaPost.makefile


clean_log:
	$(RM) *.log

clean_svg:
	$(RM) *.svg
