modded class SCR_CharacterControllerComponent : CharacterControllerComponent
{
	IEntity m_Owner;
	PlayerController m_PlayerController;
	EventHandlerManagerComponent m_EventHandlerManager = null;

	override void OnInit(IEntity owner)
	{
		m_Owner = owner;
		m_PlayerController = GetGame().GetPlayerController();
		m_EventHandlerManager = EventHandlerManagerComponent.Cast(owner.FindComponent(EventHandlerManagerComponent));
		m_EventHandlerManager.RegisterScriptHandler("OnAmmoCountChanged", this, OnAmmoCountChanged, true);
	}

	private void OnAmmoCountChanged(BaseWeaponComponent weapon, BaseMuzzleComponent muzzle, BaseMagazineComponent magazine, int ammoCount, bool isBarrelChambered)
	{
		IEntity player = m_PlayerController.GetControlledEntity();
		if (player == m_Owner)
		{
			AddCameraShake();
		}
	}

	private void AddCameraShake()
	{
		SCR_CameraShakeManagerComponent.ClearCameraShake();
		SCR_CameraShakeManagerComponent.AddCameraShake(0.5, 2, 0.01, 0.05, 0.025);
	}
}

