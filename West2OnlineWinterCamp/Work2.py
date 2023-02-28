#coding:utf-8
import os
import csv
from time import sleep
from selenium.webdriver import Chrome
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options

f = open("d:/作业2.csv", "w")
writer = csv.writer(f)
opt = Options()
opt.add_experimental_option('excludeSwitches', ['enable-automation'])
opt.add_argument('--headless')
driver = Chrome(options=opt)
driver.get('https://jwch.fzu.edu.cn/jxtz.htm')
driver.implicitly_wait(1)
num1 = 1
for page in range(5):
    reports = driver.find_elements(By.CSS_SELECTOR, '.list-gl li')
    for i in reports:
        Value_list = []
        print('Number %d ' % num1)
        print(i.text)
        link = i.find_element(By.TAG_NAME, 'a').get_attribute('href')
        print(link)
        x = i.text.split('\n')
        Time = x[0]
        y = x[1].split(' ')
        Title = y[1]
        z = y[0].split('【')[1].split('】')
        Author = z[0]
        Value_list.extend([num1, Time, Author, Title, link])
        num1 += 1
        i.find_element(By.TAG_NAME, 'a').click()
        windows = driver.window_handles
        driver.switch_to.window(windows[-1])
        files = driver.find_elements(By.XPATH, '//li[text()="附件【"]')
        if len(files) != 0:
            for x in files:
                files_link = x.find_element(By.TAG_NAME, 'a').get_attribute('href')
                print(x.text, files_link)
                a = x.text.split('【')[1].split('】')
                files_name = a[0] + a[1]
                Value_list.extend([files_name, files_link])
            writer.writerow(Value_list)
        else:
            print('无附件')
            Value_list.append('无附件')
            writer.writerow(Value_list)
        driver.switch_to.window(windows[0])
        sleep(1)
    driver.find_element(By.CSS_SELECTOR, '.p_next').click()
f.close()
os.system('pause')