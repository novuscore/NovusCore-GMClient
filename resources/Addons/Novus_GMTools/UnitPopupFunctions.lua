GM_SpeedSlider, GMMainMenu = nil
local GM_IsFlying = false

function GM_ToggleSpeedMenu()
    if (GM_SpeedSlider:IsShown()) then
        GM_SpeedSlider:Hide()
    else
        GM_SpeedSlider:Show()
    end
end

function GM_ChangeSpeed(self,value)
    GM_SetSpeed(value)
end

function GM_ToggleFlying()
    if (GM_IsFlying) then
        GM_IsFlying = false
    else
        GM_IsFlying = true
    end
    GM_ToggleFlyingMode(GM_IsFlying)
end

function GM_MainMenu_Draw(frame, level, menuList)
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
        info.tooltipOnButton = true

        for s in ("Beastmaster; Godmode"):gmatch("[^;%s][^;]*") do
            info.text = s
            UIDropDownMenu_AddButton(info, level)
        end

        info.keepShownOnClick = true
        info.text = "Speed"
        info.func = GM_ToggleSpeedMenu
        info.checked = false
        info.tooltipTitle = "A toggle option for\r\nthe speed menu."
        UIDropDownMenu_AddButton(info, level)
        
        info.text = "Flying"
        info.func = GM_ToggleFlying
        info.checked = GM_IsFlying
        info.tooltipTitle = "A toggle option for\r\nflying mode."
        UIDropDownMenu_AddButton(info, level)
   
    elseif menuList == "AccountMenu" then
        for s in ("Ban; Unban; Kick; Security; Mute"):gmatch("[^;%s][^;]*") do
            info.text = s
            UIDropDownMenu_AddButton(info, level)
        end

    elseif menuList == "DebugMenu" then
        info.keepShownOnClick = true
        info.tooltipOnButton = true

        info.text = "Terrain"
        info.func = Debug_ToggleTerrain
        info.checked = true
        info.tooltipTitle = "A toggle option for the\r\nability to see the terrain."
        UIDropDownMenu_AddButton(info, level)
        
        info.text = "Triangles"
        info.func = Debug_ToggleTriangles
        info.checked = false
        info.tooltipTitle = "A toggle option for the\r\nability to see all triangles."
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