#include "Aircraft.hpp"
#include "Game.hpp"

Aircraft::Aircraft(Type type, Game* game) : Entity(game)
	, mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

void Aircraft::updateCurrent(const GameTimer& gt)
{
	float acelX = getAcceleration().x;
	float acelZ = getAcceleration().z;

	float rotZ = getWorldRotation().z;
	float rotX = getWorldRotation().x;

	if (acelX > 0) {
		rotZ -= 60 * Rads * gt.DeltaTime();
	}
	else if(acelX < 0) {
		rotZ += 60 * Rads * gt.DeltaTime();
	}
	else {
		if (rotZ != 0) {
			if (rotZ > 0) {
				rotZ -= 30 * Rads * gt.DeltaTime();
			}
			else {
				rotZ += 30 * Rads * gt.DeltaTime();
			}
		}
	}

	if (acelZ > 0) {
		rotX += 60 * Rads * gt.DeltaTime();
	}
	else if (acelZ < 0) {
		rotX -= 60 * Rads * gt.DeltaTime();
	}
	else {
		if (rotX != 0) {
			if (rotX > 0) {
				rotX -= 30 * Rads * gt.DeltaTime();
			}
			else {
				rotX += 30 * Rads * gt.DeltaTime();
			}
		}
	}


	if (rotZ < -20 * Rads) {
		rotZ = -20 * Rads;
	}
	else if (rotZ > 20 * Rads) {
		rotZ = 20 * Rads;
	}

	if (rotX < -10 * Rads) {
		rotX = -10 * Rads;
	}
	else if (rotX > 20 * Rads) {
		rotX = 20 * Rads;
	}

	setWorldRotation(rotX, 0.0f, rotZ);

	Entity::updateCurrent(gt);
}

void Aircraft::drawCurrent(RenderContext context) const
{	
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = context.mCurrFrameResource->ObjectCB->Resource();
	auto matCB = context.mCurrFrameResource->MaterialCB->Resource();

	context.cmdList->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
	context.cmdList->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
	context.cmdList->IASetPrimitiveTopology(renderer->PrimitiveType);

	//step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(context.mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, context.mCbvSrvDescriptorSize);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

	//step19
	context.cmdList->SetGraphicsRootDescriptorTable(0, tex);
	context.cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	context.cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	context.cmdList->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);

}

void Aircraft::buildCurrent()
{
	renderer = nullptr;

	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

unsigned int Aircraft::GetCategory() const
{
	switch (mType) {
	case Eagle:
		return Category::PlayerAirCraft;

	default:
		return Category::EnemyAirCraft;
	}
}
