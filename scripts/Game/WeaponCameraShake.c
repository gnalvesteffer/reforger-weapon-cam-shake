modded class SCR_CharacterControllerComponent : CharacterControllerComponent
{
	private static PlayerController s_PlayerController;
	
	IEntity m_Owner;
	EventHandlerManagerComponent m_EventHandlerManager;

	override void OnInit(IEntity owner)
	{
		if (!s_PlayerController)
		{
			s_PlayerController = GetGame().GetPlayerController();
		}
		m_Owner = owner;
		m_EventHandlerManager = EventHandlerManagerComponent.Cast(owner.FindComponent(EventHandlerManagerComponent));
		m_EventHandlerManager.RegisterScriptHandler("OnAmmoCountChanged", this, OnAmmoCountChanged, true);
	}

	private void OnAmmoCountChanged(BaseWeaponComponent weapon, BaseMuzzleComponent muzzle, BaseMagazineComponent magazine, int ammoCount, bool isBarrelChambered)
	{
		IEntity playerControlledEntity = s_PlayerController.GetControlledEntity();
		if (m_Owner == playerControlledEntity)
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

