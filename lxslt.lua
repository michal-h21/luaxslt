require("luaxsltlib")

xml = [[
<root><child/></root>
]]

local result,result_length = luaxsltlib.transform(xml,"test.xslt","string_param","'test value'","number_param",111)
print(result)

