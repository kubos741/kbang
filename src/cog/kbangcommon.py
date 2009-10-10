# -*- coding: utf-8 -*-

from UserDict import *
from textwrap import *

constrWrapper = TextWrapper(width = 70, subsequent_indent = "         ")


def genDoxyString(doxyString, author):
    lines = []
    for line in doxyString.splitlines():
        lines.extend(wrap(line, 70))
    lines.append("@author: " + author)
    return ("/**\n" + "".join([" * " + line + "\n" for line in lines]) + " */")

class Member(UserDict):
    def __init__(self, type, name, elemName, doxyString, initVal = None):
        self.data = {}
        self["name"] = name
        self["type"] = type
        self["elemName"] = "\"" + elemName + "\""
        self["doxyString"] = doxyString
        self["initVal"] = initVal

class Struct(UserDict):
    def __init__(self, structName, elemName):
        self.data = {}
        self["structName"] = structName
        self["elemName"] = "\"" + elemName + "\""
        self["structType"] = "struct"
        self["doxyString"] = ""
        self["baseClasses"] = []
        self["baseClassesInit"] = []
        self["simpleMembers"] = []
        self["complexMembers"] = []
        self["author"] = "MacJariel"
        self.__implicitList = None

    def setImplicitList(self, scalarType, complexType = True, itemsName = None):
        assert self.__implicitList == None
        assert len(self["complexMembers"]) == 0
        self.__implicitList = scalarType
        self.__implicitListComplexType = complexType
        self.__implicitListItemsName = itemsName
        self["baseClasses"].append("public QList<%s>" % (scalarType))

    def genDecl(self):
        return "%(structType)s %(structName)s;" % self.data

    def genDef(self):
        doxyString = genDoxyString(self["doxyString"], self["author"])
        baseClasses = ", ".join(self["baseClasses"])
        if (len(baseClasses) > 0):
            baseClasses = ": " + baseClasses
        baseClassesInit = ", ".join(self["baseClassesInit"])
        resLines = [""]
        resLines.append(doxyString)
        resLines.append("struct %s%s {" % (self["structName"], baseClasses))
        inits = self.inits()
        if (len(inits) > 0):
            resLines.extend(constrWrapper.wrap("    %s(): %s {}\n" % (self["structName"], ", ".join(inits))))

        members = list(self["simpleMembers"])
        members.extend(self["complexMembers"])

        for m in members:
            resLines.append("    %(type)s %(name)s; ///%(doxyString)s" % m)
        resLines.append("};\n")
        return "\n".join(resLines)

    def genWriter(self, writer, data, isPtr, elemName = None):
        res = []
        res.append("{")
        writeStartElement = writer + "->writeStartElement(%s);"
        writeEndElement   = writer + "->writeEndElement();"
        writeTextElement  = writer + "->writeTextElement(%s, toString(%s));"
        writeAttribute    = writer + "->writeAttribute(%s, toString(%s));"
        writeStruct       = "GameStructParser::write(" + writer + ", %s);"
        writeStruct2      = "GameStructParser::write(" + writer + ", %s, %s);"
        if isPtr:
            dataThis = "(*%s)" % data
            dataMbr = data + "->"
        else:
            dataMbr = data + "."
            dataThis = data

        if elemName:
            res.append("    " +  writeStartElement % "%s ? %s : %s" % (elemName, elemName, self["elemName"]))
        else:
            res.append("    " + writeStartElement % self["elemName"])

        for s in self["simpleMembers"]:
            res.append("    " + writeAttribute % (s["elemName"], dataMbr + s["name"]))

        if (self.__implicitList):
            assert len(self["complexMembers"]) == 0
            res.append("    foreach (const %s& item, %s) {" % (self.__implicitList, dataThis))
            if (self.__implicitListComplexType):
                res.append("        " + writeStruct % "item")
            else:
                res.append("        " + writeTextElement % ("\"" + self.__implicitListItemsName + "\"", "item"))
            res.append("    }")

        for s in self["complexMembers"]:
            res.append("    " + writeStruct2 % (dataMbr + s["name"], s["elemName"]))
        res.append("    " + writeEndElement)
        res.append("}\n")
        return "\n".join(res)

    def genReader1(self):
        res = []
        res.append("{")
        for s in self["simpleMembers"]:
            res.append("    fromString(n->attribute(%(elemName)s), d.%(name)s);" % s)
        if (self.__implicitList):
            assert len(self["complexMembers"]) == 0
            res.append("    d.clear();")
            res.append("    foreach (XmlNode* ch, n->getChildren()) {")
            res.append("        %s item;" % self.__implicitList);
            if (self.__implicitListComplexType):
                res.append("        GameStructParser::read(ch, item);")
            else:
                res.append("        fromString(ch->text(), item);");
            res.append("        d.append(item);")
            res.append("    }")

        if (len(self["complexMembers"]) > 0):
            res.append("    foreach (XmlNode* ch, n->getChildren()) {")
            for s in self["complexMembers"]:
                res.append("        if (ch->name() == %(elemName)s) {" % s)
                res.append("            GameStructParser::read(ch, d.%(name)s);" % s)
                res.append("            continue;")
                res.append("        }")
            res.append("    }")
        res.append("}")
        return "\n".join(res)


    def inits(self):
        res = list(self["baseClassesInit"])
        for member in self["simpleMembers"]:
            if (member["initVal"]):
                res.append("%(name)s(%(initVal)s)" % member)
        return res


class Action(Struct):
    def __init__(self, name, elemName):
        Struct.__init__(self, "Action" + name + "Data", elemName)
        self["actionName"] = name
        self["actionType"] = name + "Type"
        self["baseClasses"].append("public ActionData")
        self["baseClassesInit"].append("ActionData(" + self["actionType"] + ")")

class GameStruct(Struct):
    def __init__(self, name, elemName):
        Struct.__init__(self, name + "Data", elemName)
        self["gameStructName"] = name
        self["gameStructType"] = name + "DataType"
        self["baseClasses"].append("public GameStruct")
        self["baseClassesInit"].append("GameStruct(" + self["gameStructType"] + ")")

