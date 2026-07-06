---
layout: default
transition: slide-left
---

# 继承层次

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">Qt 框架类继承 + 自定义多态接口 · 总计 25 个 override</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div>

```mermaid {scale: 0.65}
%%{init: {'theme':'neutral'}}%%
graph BT
    QI["QGraphicsItem"] --> QO["QGraphicsObject"]
    Q["QObject"] --> QO
    QO --> SI["ShapeItem<br/><font size=2>type / boundingRect<br/>shape / paint</font>"]
    QO --> SO["SelectionTransform<br/>OverlayItem<br/><font size=2>4 handles</font>"]
    QGV["QGraphicsView"] --> CV["CanvasView<br/><font size=2>mouse events</font>"]
    QMW["QMainWindow"] --> MW["MainWindow"]
    QW["QWidget"] --> PP["PropertyPanel"]
```

<div class="dim" style="font-size:0.75rem;margin-top:0.3rem;">Qt 类层次（灰色框）→ 项目类（白色框）</div>

</div>

<div>

```mermaid {scale: 0.6}
%%{init: {'theme':'neutral'}}%%
graph BT
    ICS["ICreationStrategy<br/><font size=2>(interface)</font>"] --> DCS["DragCreationStrategy<br/><font size=2>拖拽创建</font>"]
    ICS --> PCS["PathCreationStrategy<br/><font size=2>逐点创建</font>"]
```

</div>

</div>

<v-click>

<div style="margin-top:0.5rem;padding:0.6rem 1rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.85rem;">

<strong>override 分布</strong> — ShapeItem: 4 · CanvasView: 6 · DragCreationStrategy: 6 · PathCreationStrategy: 6 · SelectionTransformOverlayItem: 3

</div>

</v-click>

<v-click>

<div style="margin-top:0.5rem;padding:0.6rem 1rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.85rem;">

<strong>为什么 ShapeItem 继承 QGraphicsObject 而非直接 QGraphicsItem？</strong> — 获得 QObject 的信号/槽机制、元对象系统支持、Qt 父子对象生命周期管理

</div>

</v-click>

<!--
项目的类层次分为两大部分：Qt框架类继承链和自定义多态接口。ShapeItem继承QGraphicsObject而非直接QGraphicsItem，是为了获得信号槽支持和QObject的元对象系统。CanvasView继承QGraphicsView并重写鼠标事件函数，体现模板方法模式——父类定义框架，子类定制行为。ICreationStrategy是纯虚接口，6个纯虚函数没有合理的默认实现。25个override关键字保证虚函数签名的编译时校验。
-->
