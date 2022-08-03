
# QT5-cihaz-kimlik-teknik-servis

## Device Identification and Technical Service information is kept in custom MySQL and pulled into the created interface after checking username is in database or not. 
![arayüzResim](https://user-images.githubusercontent.com/66219795/182590758-ff54e0fd-4d4f-4c6a-813a-e2491758d137.png)


There are Turkish terms because the people who will use it want Turkish.
## Features

 - MySQL Connection

 - Changeable drop-down boxes

 - Username control

 - File Read for Database Connection and Username Check

 ## What is this for ?

 - Device backups and Technical Services are storing in excel files. It's hard to insert, delete and update things.
 
 - It's hard to find certain device's information so I made a search box. Below the toolbar there is a white box, It says 'filtrele' in the form of a hint.

 - Services are storing at different excel file and hard to find wanted device's services, so I made a 2 table next to each other. Left one showing devices and the right one is showing the services that selected device.

 ## What I did ?

 -  In the toolbar, there are 4 things to user can click.
 
    -- First one is 'Müşteri'(customer)
    ![musteri](https://user-images.githubusercontent.com/66219795/182594498-4e38bc74-b27b-49b5-8634-cfbd6fd633df.png)
    
    -- Second one is 'Modem Tipi'(Modem Type)
    ![modemtype](https://user-images.githubusercontent.com/66219795/182594813-ba103012-1e62-446a-a03a-2934d3a92db9.png)

    -- Third one is 'Model' (Model)
    ![model](https://user-images.githubusercontent.com/66219795/182595200-85154e1f-c472-4b10-a70a-c3e3df5c340c.png)

    -- Fourth one is 'Sim Kart'(Sim Card)
    ![simkartlar](https://user-images.githubusercontent.com/66219795/182595374-1ecd209e-49ff-47c5-8b1d-f5c86c2ffb34.png)

- On the top left, there is a plus icon. When user click this plus, a pre-interface is open.
![pre](https://user-images.githubusercontent.com/66219795/182595765-8868ea70-ad10-4d1f-a40e-752f2e00fa25.png)

--User has to select a model to go through the adding model interface. There are 7 options and 3 interfaces. When they select one of the options.
![secdialog](https://user-images.githubusercontent.com/66219795/182596155-b00a2ede-e0df-4e5c-97c8-1ad26b6e9011.png)
 After fill the blanks and select the boxes user should click the 'Ekle'(Add). When they add new device in the system. The table on the top left updated automaticly.

 -- If user double click one of the devices at the table on the top left. This shows up.
 ![inf](https://user-images.githubusercontent.com/66219795/182597012-9c910045-c28e-4d9d-a342-2d435757afc5.png)
Also if user change some of the information of the devices. The changes is shown in the table on the bottom left. The row is like : date, old value, new value and what is changed ?

-- The path of adding a service is; first choose a device that you want the add a service and then click the plus button to the right of the left-hand plus.
![services](https://user-images.githubusercontent.com/66219795/182598184-7a9cc2e2-72f4-4fa3-9d5c-8d9d32f80a63.png)
There are two service interfaces. This is the one of them for the server service. When user finish filling the blanks, has to click 'Servis Ekle'(Add Service) on the bottom right. The window closes automaticly after clicking and the table on the right on the mainwindow refresh the connection and brings the new insertions.

-- Lastly, If user want to change service informations. They should click the row that they want the changed and this window shows up.
![servisget](https://user-images.githubusercontent.com/66219795/182599020-bfe5b284-3a4c-43fa-ab99-660823554201.png)
After they finish changing things. Click the 'Güncelle'(Update) button and done.



## The whole project are **13.907** lines of code if anyone is curious.(Including the codes of the interfaces)
