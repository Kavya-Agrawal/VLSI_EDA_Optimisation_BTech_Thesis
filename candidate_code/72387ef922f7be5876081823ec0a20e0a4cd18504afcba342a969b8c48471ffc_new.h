// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87361070;
  double density_weight = 0.56150773;
  double prefix_weight = 0.41716064;
  double neighborhood_weight = 0.15282771;
  double late_weight = 0.04589947;
  double critical_weight = 0.34621250;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
