function WPDropDownDemo_Menu(frame, level, menuList)
    local info = UIDropDownMenu_CreateInfo()
   
    if level == 1 then
        info.notCheckable = true

        -- Outermost menu level
        info.text, info.hasArrow, info.menuList = "GM", true, "GMMenu"
        UIDropDownMenu_AddButton(info)
        
        info.text, info.hasArrow, info.menuList = "Account", true, "AccountMenu"
        UIDropDownMenu_AddButton(info)
        
        info.text, info.hasArrow, info.menuList = "Debug", true, "DebugMenu"
        UIDropDownMenu_AddButton(info)
   
    elseif menuList == "GMMenu" then
     -- Show the "Games" sub-menu
        for s in ("Beastmaster; Godmode; Flying; Speed"):gmatch("[^;%s][^;]*") do
            info.text = s
            UIDropDownMenu_AddButton(info, level)
        end
   
    elseif menuList == "AccountMenu" then
        -- Show the "Some other list" sub-menu
        for s in ("Ban; Unban; Kick; Security; Mute"):gmatch("[^;%s][^;]*") do
            info.text = s
            UIDropDownMenu_AddButton(info, level)
        end

    elseif menuList == "DebugMenu" then
        -- Show the "Some other list" sub-menu
        info.keepShownOnClick = true
        info.tooltipOnButton = true

        info.text = "Terrain"
        info.func = Debug_ToggleTerrain
        info.checked = true
        info.tooltipTitle = "A toggleable option to change\r\nthe ability to see the terrain."
        UIDropDownMenu_AddButton(info, level)
        
        info.text = "Triangles"
        info.func = Debug_ToggleTriangles
        info.checked = false
        info.tooltipTitle = "A toggleable option to change\r\nthe ability to see all triangles."
        UIDropDownMenu_AddButton(info, level)

        info.text = "Kill"
        info.func = nil
        info.notCheckable = true
        info.keepShownOnClick = false
        info.tooltipTitle = "Instantly kills your target"
        info.func = function() print("monkaS") end
        UIDropDownMenu_AddButton(info, level)
    end
end

--local dropDown = CreateFrame("Frame", "WPDemoDropDown", UIParent, "UIDropDownMenuTemplate")
local dropDown = CreateCustomFrame({ name = "WPDemoDropDown", text = "GM Tools", width = 80, parent = UIParent, inherits = "UIDropDownMenuTemplate", draggable = true})
UIDropDownMenu_Initialize(dropDown, WPDropDownDemo_Menu)

function dumpvar(data)
    -- cache of tables already printed, to avoid infinite recursive loops
    local tablecache = {}
    local buffer = ""
    local padder = "    "
 
    local function _dumpvar(d, depth)
        local t = type(d)
        local str = tostring(d)
        if (t == "table") then
            if (tablecache[str]) then
                -- table already dumped before, so we dont
                -- dump it again, just mention it
                buffer = buffer.."<"..str..">\n"
            else
                tablecache[str] = (tablecache[str] or 0) + 1
                buffer = buffer.."("..str..") {\n"
                for k, v in pairs(d) do
                    buffer = buffer..string.rep(padder, depth+1).."["..k.."] => "
                    _dumpvar(v, depth+1)
                end
                buffer = buffer..string.rep(padder, depth).."}\n"
            end
        elseif (t == "number") then
            buffer = buffer.."("..t..") "..str.."\n"
        else
            buffer = buffer.."("..t..") \""..str.."\"\n"
        end
    end
    _dumpvar(data, 0)
    return buffer
end


UnitPopupButtons["SET_FOCUS"] = {
    text = "Set Focus",
    dist = 0,
    func = function()
        SetFocusByToken("target")
    end
}
UnitPopupButtons["GM_PRINT_GUID"] = {
	text = "Print Guid", dist = 0, checkable = 1,
    func = function() 
        print(UnitName("target") .. "'s GUID: " .. UnitGUID("target"))
	end
}

UnitPopupButtons["GM_MENU"] = { text = "GM Menu", dist = 0, nested = 1 };
UnitPopupMenus["GM_MENU"] = { "GM_PRINT_GUID" }

tinsert(UnitPopupMenus["TARGET"], 1, "GM_MENU")
tinsert(UnitPopupMenus["PLAYER"], 1, "GM_MENU")
tinsert(UnitPopupMenus["RAID_PLAYER"], 1, "GM_MENU")
tinsert(UnitPopupMenus["PARTY"], 1, "GM_MENU")

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