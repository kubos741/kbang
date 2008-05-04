PDFCSLATEX=pdfcslate
XSLTPROC=xsltproc
DOCBOOK_HTML=/usr/share/sgml/docbook/xsl-stylesheets/xhtml/docbook.xsl

DOCBOOK_SRC=specification.xml network_protocol.xml

specification.html: specification.xml
	$(XSLTPROC) -o specification.html $(DOCBOOK_HTML) specification.xml

network_protocol.html: network_protocol.xml
	$(XSLTPROC) -o network_protocol.html $(DOCBOOK_HTML) network_protocol.xml

