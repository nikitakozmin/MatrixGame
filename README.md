# MatrixGame
Для того, чтобы разобраться в проекте достаточно [инструкции по использованию](https://github.com/nikitakozmin/MatrixGame/blob/main/src/arduino/Инструкция%20по%20применению%20макета%20матричной%20игры%20на%20Arduino.pdf) и этого файла (презентация является разъясняющей и демонстрирующей составляющей)
## :computer:[Ссылка на презентацию](https://docs.google.com/presentation/d/199Ucdy26b98wDu1JAfwCANxR6Ri18mbJcGqCX_KfC_4/edit?usp=sharing)
Указано описание теории, процесса сборки и дополнительной информации

## :joystick:[Виртуальный проект на Arduino](https://wokwi.com/projects/417100984973198337)
Проект, созданный по реальному макету Arduino с помощью эмулятора Wokwi (уже собран)

![Макет Arduino](layout.jpg)

## Ресурсы (src)
### :card_index_dividers: src/arduino/MatrixGame
Код, выполненный на Ардуино, для сборки собственной модели в жизни. Библиотека OLED_I2C, нужная для визуализации, уже находится в репозитории
#### :open_file_folder: src/arduino/MatrixGame/Emulator
Для сборки на эмуляторе нужно переместить файлы из папки в src/arduino/MatrixGame и убрать оттуда visualization_on_device.cpp

### :card_index_dividers: src/port_on_desktop
Реализация матричной игры, при которой вместо таймера игроки отправляют результаты выборов по кнопке
