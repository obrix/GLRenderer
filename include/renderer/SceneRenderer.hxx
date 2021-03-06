#ifndef SCENERENDERER_HXX
#define SCENERENDERER_HXX

#include "ModelLoader.hxx"
#include "DrawableItem.hxx"
#include "Shader.hxx"
#include "Camera.hxx"
#include "EventDispatcher.hxx"
#include "TerrainLOD.hxx"
#include "EventInterface.hxx"

#include "OceanSurface.h"
#include "TerrainGenGui.hxx"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GBufferShaderFlag
{
    albedoColor = 0x1,
    albedoTexture = 0x2,
    specularColor = 0x4,
    specularTexture = 0x8,
    normalTexture = 0x10,
    uvCoords = 0x20,
    aoTexture = 0x40,
    roughnessTexture = 0x80,
    roughnessColor = 0x100,
    displacementTexture = 0x200
};

class SceneRenderer : public EventInterface
{
public:

  SceneRenderer(GLFWwindow* p_window);

  ~SceneRenderer();

  void AddModel();

  void AddTerrain();

  void Render(GLFWwindow* p_window);

  void RenderShadowMap(GLFWwindow* p_window);

  void RenderObjects(GLFWwindow* p_window);

  void RenderTerrain(GLFWwindow* p_window);

  void RenderGBufferDebug(GLFWwindow* p_window);

  void UpdateCamera(float p_elapsedMs);

  virtual void HandleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

  virtual void HandleCursorEvent(double p_xpos, double p_ypos,
    double p_deltaX, double p_deltaY);

  typedef std::map<std::string, unsigned int> UintMap;

private:

  //Disable copy
  SceneRenderer(SceneRenderer const& p_other);

  void GenerateGBufferShader(rx::Mesh const& p_mesh, rx::MaterialPtr p_material);

  std::string GeneratePreprocessorDefine(unsigned int p_gBufferFlags);

  void PrepareTwoTrianglesBuffer();

  void PrepareGBufferFrameBufferObject(int p_width, int p_height);

  void PrepareShadowMapFrameBufferObject(int p_width, int p_height);

  void ComputeNearFarProjection();

  TerrainGenGui m_terrainGUI;

  std::vector<DrawableItem*> m_drawableItems;

  typedef std::map<unsigned int, ShaderPtr> GBufferShaderMap;
  GBufferShaderMap m_gbufferShaders;

  UintMap m_shaderForMaterial;

  std::vector<rx::MaterialPtr> m_materialPtrs;

  Camera m_mainCamera;

  Shader m_renderShader;

  Shader m_shadowMapShader;

  std::shared_ptr<TerrainLOD> m_terrain;
  std::shared_ptr<TerrainLOD> m_water;
  rx::OceanSurface m_surf;
  unsigned int m_watersurfTex;

  //For 2 triangles support render
  unsigned int m_vBufferId;
  unsigned int m_iBufferId;
  unsigned int m_renderVertexArray;

  //Gbuffer render target
  unsigned int m_gbufferFBO;
  unsigned int m_renderTarget1;
  unsigned int m_renderTarget2;
  unsigned int m_renderTarget3;
  unsigned int m_renderTarget4;

  //ShadowMap target
  unsigned int m_shadowMapFBO;
  unsigned int m_shadowMapTextureId1;
  glm::mat4 m_shadowMapMatrix;
  glm::mat4 m_invProjMatrix;
  glm::mat4 m_invViewMatrix;

  glm::vec3 m_sunLightDirection;

  RenderingDebugInfo* m_renderParam;
};

#endif
