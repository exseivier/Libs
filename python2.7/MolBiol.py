#!/usr/bin/env python


class Dna (object):

	def __init__(self):
		pass
	
	def pgc(self, seq):
		"""
			Calculates the guanine and cytosine percentaje in a sequence
			(String) -> Float
			
		"""
		self.seq = seq
		p = 0.0
		for ch in self.seq:
			if ch.upper() == "G" or ch.upper() == "C":
				p += 1
			else:
				pass
			
		return p / float(len(seq))
		
		#END pgc() FUNCTION
	
	def rvc(self, seq):
		"""
			Returns the reverse complementary sequence
			(String) -> String
			
		"""
		arvc = []
		self.seq = seq
		i = 0
		for ch in seq:
			i += 1
			if ch.upper() == "A":
				arvc.append("T")
			elif ch.upper() == "C":
				arvc.append("G")
			elif ch.upper() == "G":
				arvc.append("C")
			elif ch.upper() == "T":
				arvc.append("A")
			else:
				print "Strange nucleotide %s at position %s" % (ch, i)
		
		return "".join(reversed(arvc))
		
		#END rvc() FUNCTION
	
	def palseq(self, seq):
		"""
			Returns TRUE or FALSE if a sequence is palindrome or not respecitvely
			(String) -> Bool
			
		"""
		self.seq = seq
		if len(self.seq) <= 1:
			return True
		else:
			if self.seq[0].upper() == self.rvc(self.seq[-1]).upper():
				return self.palseq(seq[1:-1])
			else:
				return False
		
		#END palseq() FUNCTION
	
	def skewgc(self, seq):
		"""
			Returns the skew value of guanines over cytosine
			(String) -> Integer
		"""
		self.seq = seq
		c = 0
		for nt in self.seq:
			if nt.upper() == "G":
				c += 1
			elif nt.upper() == "C":
				c -= 1
			else:
				pass
		
		return c
		
		#END skewgc() FUNCTION

def main():
	pass
				

if __name__ == '__main__':
	main()


