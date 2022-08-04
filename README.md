
# QT5 Cihaz Kimlik Teknik Servis

## Device Identification and Technical Service information is kept in custom MySQL and pulled into the created interface after checking username is in database or not. 
![1](https://user-images.githubusercontent.com/66219795/182785075-8dd3a605-7e5f-443a-9fff-d5557f042dad.png)


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
    ![2](https://user-images.githubusercontent.com/66219795/182785221-162816f9-9d90-4a36-8099-9f4ea1f2b86e.png)
    
    -- Second one is 'Modem Tipi'(Modem Type)
    ![3](https://user-images.githubusercontent.com/66219795/182785295-edbbf193-52ff-4471-aa78-8d93f6d90e0c.png)

    -- Third one is 'Model' (Model)
    ![4](https://user-images.githubusercontent.com/66219795/182785400-7708277d-326d-4144-824b-e64d4b97bd0c.png)

    -- Fourth one is 'Sim Kart'(Sim Card)
    ![5](https://user-images.githubusercontent.com/66219795/182785471-fd1cb5fc-87c9-47da-87ea-eca7b3a78bc3.png)

- On the top left, there is a plus icon. When user click this plus, a pre-interface is open.
![6](https://user-images.githubusercontent.com/66219795/182785580-975b106b-34d8-4c67-873b-9a9ed5a9bd3d.png)

--User has to select a model to go through the adding model interface. There are 7 options and 3 interfaces. When they select one of the options.
![7](https://user-images.githubusercontent.com/66219795/182785621-3520dcf2-cbb7-47fd-8fd3-4712182dba51.png)
 After fill the blanks and select the boxes user should click the 'Ekle'(Add). When they add new device in the system. The table on the top left updated automaticly.

 -- If user double click one of the devices at the table on the top left. This shows up.
 ![8](https://user-images.githubusercontent.com/66219795/182785671-9fbd395e-4337-411b-892b-e511dacbee3c.png)
Also if user change some of the information of the devices. The changes is shown in the table on the bottom left. The row is like : date, old value, new value and what is changed ?

-- The path of adding a service is; first choose a device that you want the add a service and then click the plus button to the right of the left-hand plus.
![9](https://user-images.githubusercontent.com/66219795/182785717-18c80ed8-7b5d-4f30-a127-410008d63069.png)
There are two service interfaces. This is the one of them for the server service. When user finish filling the blanks, has to click 'Servis Ekle'(Add Service) on the bottom right. The window closes automaticly after clicking and the table on the right on the mainwindow refresh the connection and brings the new insertions.

-- Lastly, If user want to change service informations. They should click the row that they want the changed and this window shows up.
![10](https://user-images.githubusercontent.com/66219795/182785762-dc4b3146-9c4f-440f-adb8-aa2a81e74a8a.png)
After they finish changing things. Click the 'Güncelle'(Update) button and done.

