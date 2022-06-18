import sys
import getopt
from sly import Lexer, Parser

USAGE = f"Usage: python {sys.argv[0]} [--help] [--output <file>] file"

OPCODES = {
	"nop": 		0x00,
	"lda_i": 	0x01,
	"lda_a": 	0x11,
	"sta_a": 	0x12,
	"jmp_a": 	0x05,
	"beq_a": 	0x25,
	"bcs_a": 	0x15,
	"adc_i": 	0x08,
	"adc_a": 	0x18,
	"sbc_i": 	0x09,
	"sbc_a": 	0x19,
	"cmp_i": 	0x0B,
	"cmp_a": 	0x1B,
	"in": 		0x07,
	"out": 		0x06
}

class AsmLexer(Lexer):
	tokens = { NAME, OPCODE, NUMBER, END }
	literals = { "+", "#", "=", ":" }
	ignore = ' \t'
	
	# Tokens
	OPCODE		= r'nop|lda|sta|jmp|beq|bcs|adc|sbc|cmp|out|in'
	NAME			= r'[a-zA-Z_][a-zA-Z0-9_]*'
	NUMBER		= r'\$[0-9a-fA-F]+|\-?\d+'
	
	@_(r'([ \t]*\n)+')
	def END(self, t):
		self.lineno += t.value.count('\n')
		return t
	
	# Ignored pattern
	ignore_comment = r';.*'
        
	def error(self, t):
		print("Illegal character '%s'" % t.value[0])
		self.index += 1

class AsmParser(Parser):
	tokens = AsmLexer.tokens
	
	def __init__(self):
		self.parser_pass = 0
		self.pc = 0
		self.variables = { }
		self.code = [ ]
	
	def nextPass(self, tokens):
		self.parse(tokens)
		self.parser_pass += 1
		return self
		
	def getCode(self):
		return self.code;

	# statement:
		
	@_('statement assign_statement END')
	def statement(self, p):
		pass
		
	@_('statement labeled_statement END')
	def statement(self, p):
		pass
		
	@_('statement operation_statement END')
	def statement(self, p):
		pass
	
	@_('END')
	def statement(self, p):
		pass
			
	@_('')
	def statement(self, p):
		pass
		
	# assign_statement:

	@_('NAME "=" expression')
	def assign_statement(self, p):
		if self.parser_pass == 0:
			self.variables[p.NAME] = p.expression
			if p.expression == -1:
				raise SystemExit("Error at line " + str(p.lineno) + ": " + p.NAME + " is used in an assigment but never been declared before")
	
	# labeled_statement:
		
	@_('NAME ":"')
	def labeled_statement(self, p):
		if self.parser_pass == 0:
			self.variables[p.NAME] = self.pc
		
	# operation_statement:
	
	@_('OPCODE')
	def operation_statement(self, p):
		if self.parser_pass == 1:
			self.code.append(OPCODES[p.OPCODE])
		self.pc += 1
		
	@_('OPCODE expression')
	def operation_statement(self, p):
		if self.parser_pass == 1:
			self.code.append(OPCODES[p.OPCODE + "_a"])
			self.code.append(p.expression)
		self.pc += 2
		  
	@_('OPCODE "#" expression')
	def operation_statement(self, p):
		if self.parser_pass == 1:
			self.code.append(OPCODES[p.OPCODE + "_i"])
			self.code.append(p.expression)
		self.pc += 2
	  
	# expression:
	
	@_('expression "+" primary_expression')
	def expression(self, p):
		return p.expression + p.primary_expression
	
	@_('primary_expression')
	def expression(self, p):
		return p.primary_expression
		
	@_('NUMBER')
	def primary_expression(self, p):
		if p.NUMBER.startswith('$'):
			return int(p.NUMBER[1:], 16)
		else:
			return int(p.NUMBER)
			
	@_('NAME')
	def primary_expression(self, p):
		try:
			return self.variables[p.NAME]
		except LookupError:
			return -1
			
class CodeGenerator:

	def __init__(self):
		self.parser_pass = 0
		self.pc = 0
		self.variables = { }
		self.code = [ ]

	def generate(self, code):
		return bytearray(code) + bytearray([0x00] * (8192 - len(code)))

def parseArgs():
	options, arguments = getopt.getopt(
		sys.argv[1:],                      
		'ho:',                            
		["help", "output="])
      
	if not arguments or len(arguments) > 3:
		raise SystemExit(USAGE)    
	try:
		inFile = arguments[0]
	except ValueError:
		raise SystemExit(USAGE)
        
	outFile = "a.out"  
	for o, a in options:
		if o in ("-h", "--help"):
			raise SystemExit(USAGE)
		if o in ("-o", "--output"):
			if inFile != a:
				outFile = a

	return inFile, outFile

if __name__ == '__main__':

	inFile, outFile = parseArgs()
              
	with open(inFile, 'r') as in_file:
		text = in_file.read()
		
		lexer = AsmLexer()
		parser = AsmParser()
		generator = CodeGenerator()
		
		# for tok in lexer.tokenize(text):
		# 	print('type=%r, value=%r' % (tok.type, tok.value))
    
		rom = generator.generate(
			parser
				.nextPass(lexer.tokenize(text))
				.nextPass(lexer.tokenize(text))
				.getCode());
		
		with open(outFile, "wb") as out_file:
			out_file.write(rom)

