#Python Code
class Employee:

    num_of_emps = 0
    raise_amount = 1.04
    
    def __init__(self,first,last,pay):
        self.first = first
        self.last = last
        self.pay = pay
        self.email = first+'.'+last+'@company.com'

        Employee.num_of_emps +=1
    def fullname(self):
        return '{} {}'.format(self.first, self.last)
    
    def apply_raise(self):
        self.pay = int(self.pay*self.raise_amount)

emp_1 = Employee('Conney','Schafer','6000')
emp_2 = Employee('Anna','Buits','5000')
        
        


#print(Employee.num_of_emps)
#print(apply_raise(emp_1))
print(emp_1.pay)
#print(emp_1.apply_raise())
print(emp_2.apply_raise())
print(emp_2.pay)




