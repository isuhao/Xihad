local InputSimulator = {
	playerStateMachine = nil,
}
InputSimulator.__index = InputSimulator

function InputSimulator.new(psm)
	return setmetatable({
			playerStateMachine = psm
		}, InputSimulator)
end

function InputSimulator:selectWarrior(name)
	local object = g_scene:findObject(c(name))
	assert(object)
	self.playerStateMachine:postCommand('onWarriorSelected', object, 1)
end

function InputSimulator:selectTile(tile)
	assert(tile)
	self.playerStateMachine:postCommand('onTileSelected', tile, 2)
end

function InputSimulator:selectTileAt(x, y)
	local tile = g_chessboard:getTile(x, y)
	self:selectTile(tile)
end

function InputSimulator:selectCommand(mainCmd, subCmd)
	self.playerStateMachine:postCommand('onUICommand', mainCmd, subCmd, 'Select')
end

return InputSimulator