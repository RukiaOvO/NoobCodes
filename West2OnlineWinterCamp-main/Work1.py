class Goods(object):
    def __init__(self, rank, name, price, number_all, number_rest):
        if isinstance(rank, int) == True \
            and isinstance(name, str) == True \
            and isinstance(price, float) == True \
            and isinstance(number_all, int) == True \
            and isinstance(number_rest, int) == True:
            self.__rank = rank
            self.__name = name
            self.__price = price
            self.__number_all = number_all
            self.__number_rest = number_rest
        else:
            raise ValueError('输入正确的信息')
    def display(self):
        print('商品序号%d' %self.__rank)
        print('商品名称%s' %self.__name)
        print('商品单价%.2f' %self.__price)
        print('商品总数%d' %self.__number_all)
        print('商品剩余数%d' %self.__number_rest)
    def income(self):
        num1 = self.__number_all - self.__number_rest
        price_all = self.__price * num1
        print('已售商品 %s 价值为%.2f' %(self.__name, price_all))
    def setdata(self):
        self.__rank = int(input('更改商品 %s 序号为:' %self.__name))
        self.__name = str(input('更改商品 %s 名称为:' %self.__name))
        self.__price = float(input('更改商品 %s 单价为:' %self.__name))
        self.__number_all = int(input('更改商品 %s 总数为:' %self.__name))
        self.__number_rest = int(input('更改商品 %s 剩余数为:' %self.__name))