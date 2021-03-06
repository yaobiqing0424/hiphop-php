/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __CLASS_STATEMENT_H__
#define __CLASS_STATEMENT_H__

#include <compiler/statement/interface_statement.h>
#include <compiler/expression/modifier_expression.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

DECLARE_BOOST_TYPES(ClassStatement);

class ClassStatement : public InterfaceStatement {
public:
  ClassStatement(STATEMENT_CONSTRUCTOR_PARAMETERS,
                 int type, const std::string &name,
                 const std::string &parent, ExpressionListPtr base,
                 const std::string &docComment,
                 StatementListPtr stmt,
                 ExpressionListPtr attrList);

  DECLARE_BASE_STATEMENT_VIRTUAL_FUNCTIONS;
  virtual bool hasDecl() const { return true; }
  virtual bool hasImpl() const;

  // implementing IParseHandler
  virtual void onParse(AnalysisResultConstPtr ar, FileScopePtr scope);
  bool ignored() const { return m_ignored;}

  virtual std::string getName() const;
  virtual void getAllParents(AnalysisResultConstPtr ar,
                             std::vector<std::string> &names);
  void getCtorAndInitInfo(bool &needsCppCtor, bool &needsInit);
  StatementPtr addClone(StatementPtr origStmt);
private:
  int m_type;
  std::string m_parent;
  std::string m_originalParent;
  bool m_ignored;

  static void GetCtorAndInitInfo(
      StatementPtr s, bool &needsCppCtor, bool &needsInit);
  void outputCPPClassDecl(CodeGenerator &cg, AnalysisResultPtr ar,
                          const char *clsName, const char *originalName,
                          const char *parent);
  void outputJavaFFIConstructor(CodeGenerator &cg, AnalysisResultPtr ar,
                                FunctionScopePtr cons);
  void outputJavaFFICPPCreator(CodeGenerator &cg, AnalysisResultPtr ar,
                               FunctionScopePtr cons);
};

///////////////////////////////////////////////////////////////////////////////
}
#endif // __CLASS_STATEMENT_H__
