// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69514373;
  double density_weight = 0.07860529;
  double prefix_weight = 0.13806284;
  double neighborhood_weight = 0.05774093;
  double late_weight = 0.29986917;
  double critical_weight = 0.08897389;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
