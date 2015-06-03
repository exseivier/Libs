#!/usr/bin/env python

import math

class Utils (object):

	def __init__(self):
		pass

	def ed(self, p, q):
		"""
			Calculates the euclidean distance between two vectors
			(Array, Array) -> Float
			ed(p,q) = sqrt(mult((pi - qi)^2))
		"""
		
		
		if p == None or q == None:
			print "There are not enough arguments"
			return 0
		
		if p == [] or q == []:
			print "The arrays are empty"
			return 0
		
		if len(p) != len(q):
			print "Vector arguments have different size"
			return 0
		
		self.p = p
		self.q = q
		resta = 0.0
		multi = 0.0
		for i in xrange(len(self.p)):
			resta = math.pow((self.p[i] - self.q[i]), 2)
			multi += resta
		
		return math.sqrt(multi)
		
		#END ed() FUNCTION
	
	def suma(self, x):
		"""
			Sums the numeric elements o an array
			(Array) -> Float
			suma(x) = xi + xi+1 + xi+2 + ... + xn
		"""
		self.x = x
		result = 0.0
		for num in self.x:
			result += num
		
		return result
		
		#END suma() FUNCTION
	
	def media(self, x):
		"""
			Calculates the mean of a bunch of data
			(Array) -> Float
			media(x) = suma(x)/len(x)
		"""
		self.x = x
		result = 0.0
		for num in self.x:
			result += num
		
		return result / float(len(x))
		
		#END media() FUNCTION
	
	


def main():
	pass


if __name__ == '__main__':
	main()


