local SimpleRound = function(val,valStep)
    return floor(val/valStep)*valStep
end

function CreateSlider(parent, name, title, minVal, maxVal, valStep)
    local slider = CreateFrame("Slider", name, parent, "OptionsSliderTemplate")
    local editbox = CreateFrame("EditBox", "$parentEditBox", slider, "InputBoxTemplate")
    slider:SetMinMaxValues(minVal, maxVal)
    slider:SetValue(1)
    slider:SetValueStep(valStep)
    slider.text = _G[name.."Text"]
    slider.text:SetText(title)
    slider.textLow = _G[name.."Low"]
    slider.textHigh = _G[name.."High"]
    slider.textLow:SetText(floor(minVal))
    slider.textHigh:SetText(floor(maxVal))
    slider.textLow:SetTextColor(1,1,1)
    slider.textHigh:SetTextColor(1,1,1)
    editbox:SetSize(25,30)
    editbox:ClearAllPoints()
    editbox:SetPoint("BOTTOM", slider, "RIGHT", -15, 0)
    editbox:SetText(slider:GetValue())
    editbox:SetAutoFocus(false)
    slider:SetScript("OnValueChanged", function(self,value)
      self.editbox:SetText(SimpleRound (value,valStep))
    end)
    slider:EnableMouseWheel(true)
    slider:SetScript('OnMouseWheel', function(self, delta)
        local val = editbox:GetText()
        if tonumber(val) then
            local finalVal = val
            if (delta > 0) then
                finalVal = finalVal + valStep
            else
                finalVal = finalVal - valStep
            end
           self:SetValue(finalVal)
        end
    end)
    editbox:SetScript("OnTextChanged", function(self)
      local val = self:GetText()
      if tonumber(val) then
         self:GetParent():SetValue(val)
      end
    end)
    editbox:SetScript("OnEnterPressed", function(self)
      local val = self:GetText()
      if tonumber(val) then
         self:GetParent():SetValue(val)
         self:ClearFocus()
      end
    end)
    slider.editbox = editbox
    slider:SetPoint("CENTER", UIParent, "CENTER", 670, 215)
    return slider
end
function CreateCustomFrame(frameDetails) -- width, height, scale, texturePath, draggable
    local frame = CreateFrame(frameDetails.typea or "Frame", frameDetails.name, frameDetails.parent, frameDetails.inherits)

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