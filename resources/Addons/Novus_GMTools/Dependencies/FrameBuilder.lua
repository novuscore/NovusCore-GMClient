function CreateCustomFrame(frameDetails) -- width, height, scale, texturePath, draggable
    local frame = CreateFrame(frameDetails.type or "Frame", frameDetails.name, frameDetails.parent, frameDetails.inherits)

    if (frameDetails.width) then
        frame:SetWidth(frameDetails.width)
    end

    if (frameDetails.height) then
        frame:SetHeight(frameDetails.height)
    end

    if (not frameDetails.scale) then
        frameDetails.scale = 1
    end

    if (frameDetails.text) then
        UIDropDownMenu_SetWidth(frame, frameDetails.width)
        UIDropDownMenu_SetText(frame, frameDetails.text)
    end

    frame:SetScale(frameDetails.scale)
    
    local texture = frame:CreateTexture(nil, "BACKGROUND")
    texture:SetTexture(frameDetails.texturePath)
    texture:SetAllPoints(frame)

    if (frameDetails.draggable) then
        frame:EnableMouse(true)
        frame:SetMovable(true)
        frame:RegisterForDrag("LeftButton")
        frame:SetScript("OnDragStart", function() this:StartMoving() end)
        frame:SetScript("OnDragStop", function() this:StopMovingOrSizing() end)
    end
    
    frame:SetPoint("CENTER", UIParent, "CENTER", 0, 0)
    return frame
end

