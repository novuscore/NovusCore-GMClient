UnitPopupButtons["GM_MENU"] = { text = "GM Menu", dist = 0, nested = 1 };
UnitPopupMenus["GM_MENU"] = { "GM_PRINT_GUID" }
tinsert(UnitPopupMenus["TARGET"], 1, "GM_MENU")
tinsert(UnitPopupMenus["PLAYER"], 1, "GM_MENU")
tinsert(UnitPopupMenus["RAID_PLAYER"], 1, "GM_MENU")
tinsert(UnitPopupMenus["PARTY"], 1, "GM_MENU")

UnitPopupButtons["SET_FOCUS"] = 
{
    text = "Set Focus",
    dist = 0,
    func = function()
        SetFocusByToken("target")
    end
}
UnitPopupButtons["GM_PRINT_GUID"] = 
{
	text = "Print Guid", dist = 0, checkable = 1,
    func = function() 
        print(UnitName("target") .. "'s GUID: " .. UnitGUID("target"))
	end
}

hooksecurefunc("UnitPopup_ShowMenu", function()
    for i=1, UIDROPDOWNMENU_MAXBUTTONS do
        local button = _G["DropDownList"..UIDROPDOWNMENU_MENU_LEVEL.."Button"..i];
		if button.value == "SET_FOCUS" then
            button.func = UnitPopupButtons["SET_FOCUS"].func
        elseif button.value == "GM_PRINT_GUID" then
            button.func = UnitPopupButtons["GM_PRINT_GUID"].func
        end
	end
end)