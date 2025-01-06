# MatrixGame
Для того, чтобы разобраться в проекте достаточно [инструкции по использованию](https://github.com/nikitakozmin/MatrixGame/blob/main/src/ardruino/Инструкция%20по%20применению%20макета%20матричной%20игры%20на%20Arduino.pdf) и этого файла (презентация является разъясняющей и демонстрирующей составляющей)
## :computer:[Ссылка на презентацию](https://docs.google.com/presentation/d/199Ucdy26b98wDu1JAfwCANxR6Ri18mbJcGqCX_KfC_4/edit?usp=sharing)
Указано описание теории, процесса сборки и дополнительной информации

## :joystick:[Виртуальный проект на Ardruino](https://wokwi.com/projects/417100984973198337)
Проект, созданный по реальному макету Ardruino с помощью эмулятора Wokwi (уже собран)

![Макет Ardruino](layout.jpg)

## Ресурсы (src)
### :card_index_dividers: src/ardruino/MatrixGame
Код, выполненный на Ардруино, для сборки собственной модели в жизни. Библиотека OLED_I2C, нужная для визуализации, уже находится в репозитории
#### :open_file_folder: src/ardruino/MatrixGame/Emulator
Для сборки на эмуляторе нужно переместить файлы из папки в src/ardruino/MatrixGame и убрать оттуда visualization_on_device.cpp

### :card_index_dividers: src/port_on_desktop
Реализация матричной игры, при которой вместо таймера игроки отправляют результаты выборов по кнопке
