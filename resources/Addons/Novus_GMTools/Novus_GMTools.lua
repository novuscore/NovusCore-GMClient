GM_SpeedSlider = CreateSlider(UIParent, "MySlider", "Speed", 1, 50, 1)
GM_SpeedSlider:HookScript("OnValueChanged", GM_ChangeSpeed)
GM_SpeedSlider:Hide()

GMMainMenu = CreateCustomFrame({ name = "GMMainMenu", text = "GM Tools", width = 80, parent = UIParent, inherits = "UIDropDownMenuTemplate", draggable = true})
UIDropDownMenu_Initialize(GMMainMenu, GM_MainMenu_Draw)
