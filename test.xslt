<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:param name="string_param" />
<xsl:param name="number_param" />
  <xsl:template match="/">
    <html>
      <head>
    <title>LuaXslt test</title>
      </head>

      <body>
      <xsl:value-of select="count(./descendant-or-self::*)" />|<xsl:value-of select="$string_param" />|<xsl:value-of select="$number_param" />
      </body>
    </html>
  </xsl:template>

</xsl:stylesheet>

